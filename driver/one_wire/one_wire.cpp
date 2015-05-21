#include "driver/one_wire/one_wire.h"
#include "hal/time.h"

namespace one_wire
{



one_wire::one_wire(port Id) : gpio::gpio(Id)
{

}

one_wire::~one_wire()
{

}

// true meens ok, false : error
bool one_wire::reset()
{
	/* Line low, and wait 480us */
	low();
	set_as_digital_output(::gpio::PushPull);
	time::usleep(480);
	
	/* Release line and wait for 70us */
	set_as_digital_input(::gpio::PullUp);
	time::usleep(70);
	
	/* Check bit value */
	uint8_t i = get_input_value();
	
	/* Delay for 410 us */
	time::usleep(410);
	
	/* Return value of presence pulse, 0 = OK, 1 = ERROR */
	return (i == 0);
}

void one_wire::write_byte(uint8_t byte)
{
	uint8_t i = 8;
	/* Write 8 bits */
	while (i--) {
		/* LSB bit is first */
		write_bit(byte & 0x01);
		byte >>= 1;
	}
}

uint8_t one_wire::read_byte()
{
	uint8_t i = 8, byte = 0;
	while (i--) {
		byte >>= 1;
		byte |= (read_bit() << 7);
	}
	
	return byte;
}

void one_wire::write_bit(uint8_t bit) {
	if (bit) {
		/* Set line low */
		set_as_digital_output(::gpio::PushPull);
		low();
		time::usleep(10);
		
		/* Bit high */
		set_as_digital_input(::gpio::PullUp);
		
		/* Wait for 55 us and release the line */
		time::usleep(55);
	}
	else
	{
		/* Set line low */
		set_as_digital_output(::gpio::PushPull);
		low();
		time::usleep(65);
		
		/* Bit high */
		set_as_digital_input(::gpio::PullUp);

		/* Wait for 5 us and release the line */
		time::usleep(5);
	}

}

uint8_t one_wire::read_bit()
{
	uint8_t bit = 0;
	
	/* Line low */
	set_as_digital_output(::gpio::PushPull);
	low();
	time::usleep(3);
	
	/* Release line */
	set_as_digital_input(::gpio::PullUp);
	time::usleep(10);
	
	/* Read line value */
	if (get_input_value())
	{
		/* Bit is HIGH */
		bit = 1;
	}
	
	/* Wait 50us to complete 60us period */
	time::usleep(50);
	
	/* Return bit value */
	return bit;
}


void one_wire::init_search(search_context* pSearchCtx)
{
	pSearchCtx->LastDiscrepancy			= 0;
	pSearchCtx->SearchTerminated		= false;
	pSearchCtx->LastFamilyDiscrepancy	= 0;
}

uint8_t one_wire::get_next_periph(search_context* pSearchCtx, uint8_t ROM_NO[8])
{
	uint8_t id_bit_number;
	uint8_t last_zero, rom_byte_number, search_result;
	uint8_t id_bit, cmp_id_bit;
	uint8_t rom_byte_mask, search_direction;

	/* Initialize for search */
	id_bit_number	= 1;
	last_zero		= 0;
	rom_byte_number	= 0;
	rom_byte_mask	= 1;
	search_result	= 0;

	// if the last call was not the last one
	if (!pSearchCtx->SearchTerminated)
	{

		// 1-Wire reset
		if (! reset()) {
			/* Reset the search */
			init_search(pSearchCtx);
			return 0;
		}
	
		// issue the search command 
		write_byte(CMD_SEARCHROM);

		// loop to do the search
		do
		{
			// read a bit and its complement
			id_bit			= read_bit();
			cmp_id_bit		= read_bit();

			/*
			Bit Search Information
			Bit (true) 	Bit (complement) 	Information Known
			0 	0 	There are both 0s and 1s in the current bit position of the participating ROM numbers. This is a discrepancy.
			0 	1 	There are only 0s in the bit of the participating ROM numbers.
			1 	0 	There are only 1s in the bit of the participating ROM numbers.
			1 	1 	No devices participating in search.
			*/
			
			// check for no devices on 1-wire
			if ((id_bit == 1) && (cmp_id_bit == 1))
			{
				break;
			}
			else
			{
				// all devices coupled have 0 or 1
				if (id_bit != cmp_id_bit)
				{
					search_direction = id_bit;  // bit write value for search
				}
				else
				{
					// if this discrepancy is before the Last Discrepancy
					// on a previous next then pick the same as last time
					if (id_bit_number < pSearchCtx->LastDiscrepancy)
					{
						search_direction = ((ROM_NO[rom_byte_number] & rom_byte_mask) > 0);
					}
					else
					{
						// if equal to last pick 1, if not then pick 0
						search_direction = (id_bit_number == pSearchCtx->LastDiscrepancy);
					}
					
					// if 0 was picked then record its position in LastZero
					if (search_direction == 0)
					{
						last_zero = id_bit_number;

						// check for Last discrepancy in family
						if (last_zero < 9)
						{
							pSearchCtx->LastFamilyDiscrepancy = last_zero;
						}
					}
				}

				// set or clear the bit in the ROM byte rom_byte_number
				// with mask rom_byte_mask
				if (search_direction == 1)
				{
					ROM_NO[rom_byte_number] |= rom_byte_mask;
				} else {
					ROM_NO[rom_byte_number] &= ~rom_byte_mask;
				}
				
				// serial number search direction write bit
				write_bit(search_direction);

				// increment the byte counter id_bit_number
				// and shift the mask rom_byte_mask
				id_bit_number++;
				rom_byte_mask <<= 1;

				// if the mask is 0 then go to new SerialNum byte rom_byte_number and reset mask
				if (rom_byte_mask == 0)
				{
					rom_byte_number++;
					rom_byte_mask = 1;
				}
			}
		} while (rom_byte_number < 8);  // loop until through all ROM bytes 0-7

		// if the search was successful then
		if (!(id_bit_number < 65))
		{
			// search successful so set LastDiscrepancy,LastDeviceFlag,search_result
			pSearchCtx->LastDiscrepancy = last_zero;

			// check for last device
			if (pSearchCtx->LastDiscrepancy == 0)
			{
				pSearchCtx->SearchTerminated = true;
			}

			search_result = 1;
		}
	}

	// if no device found then reset counters so next 'search' will be like a first
	if (!search_result || !ROM_NO[0])
	{
		init_search(pSearchCtx);
		search_result = 0;
	}

	return search_result;

}

void one_wire::select (uint8_t ROM_NO[8])
{
	uint8_t i;
	write_byte(CMD_MATCHROM);
	
	for (i = 0; i < 8; i++)
	{
		write_byte(ROM_NO[i]);
	}
}

static const uint8_t dscrc_table[] = {
      0, 94,188,226, 97, 63,221,131,194,156,126, 32,163,253, 31, 65,
    157,195, 33,127,252,162, 64, 30, 95,  1,227,189, 62, 96,130,220,
     35,125,159,193, 66, 28,254,160,225,191, 93,  3,128,222, 60, 98,
    190,224,  2, 92,223,129, 99, 61,124, 34,192,158, 29, 67,161,255,
     70, 24,250,164, 39,121,155,197,132,218, 56,102,229,187, 89,  7,
    219,133,103, 57,186,228,  6, 88, 25, 71,165,251,120, 38,196,154,
    101, 59,217,135,  4, 90,184,230,167,249, 27, 69,198,152,122, 36,
    248,166, 68, 26,153,199, 37,123, 58,100,134,216, 91,  5,231,185,
    140,210, 48,110,237,179, 81, 15, 78, 16,242,172, 47,113,147,205,
     17, 79,173,243,112, 46,204,146,211,141,111, 49,178,236, 14, 80,
    175,241, 19, 77,206,144,114, 44,109, 51,209,143, 12, 82,176,238,
     50,108,142,208, 83, 13,239,177,240,174, 76, 18,145,207, 45,115,
    202,148,118, 40,171,245, 23, 73,  8, 86,180,234,105, 55,213,139,
     87,  9,235,181, 54,104,138,212,149,203, 41,119,244,170, 72, 22,
    233,183, 85, 11,136,214, 52,106, 43,117,151,201, 74, 20,246,168,
    116, 42,200,150, 21, 75,169,247,182,232, 10, 84,215,137,107, 53
};


uint8_t crc8( uint8_t *addr, uint8_t len)
{
	uint8_t crc = 0;

	while (len--) {
		crc = dscrc_table[(crc ^ *addr++)];
	}
	return crc;
}

} // end namespace
