#include <driver/ds18b20/ds18b20.h>
#include <cstring>
#include <hal/time.h>

namespace ds18b20
{

	const uint8_t DS18B20_ID			= 0x28;
	const uint8_t CMD_TAKE_TEMPERATURE	= 0x44;

	ds18b20::ds18b20(port Id) : ::one_wire::one_wire(Id)
	{
		
		::one_wire::search_context search_ctx;
		init_search(&search_ctx);

		unsigned int nCount = 0;
		uint8_t ROM_NO[8];
		while (get_next_periph(&search_ctx, ROM_NO))
		{
			if (ROM_NO[0] == DS18B20_ID)
				break;
			++nCount;
		}

		if (ROM_NO[0] == DS18B20_ID)
		{
			memcpy(_ROM_NO, ROM_NO, sizeof(ROM_NO));	
		}
		else
		{
			memset(_ROM_NO, 0, sizeof(ROM_NO));
		}
	}

	ds18b20::~ds18b20()
	{

	}


	float ds18b20::get_temperature()
	{
		if (_ROM_NO[0] != DS18B20_ID)
			return 0.0;

		reset();
		select(_ROM_NO);


		write_byte(CMD_TAKE_TEMPERATURE);      // On lance une prise de mesure de température
		time::usleep(800);             		// Et on attend la fin de la mesure

		reset();						// On reset le bus 1-Wire
		select(_ROM_NO);        			// On sélectionne le DS18B20
		write_byte(::one_wire::CMD_RSCRATCHPAD);	// On envoie une demande de lecture du scratchpad

		time::usleep(10);
		uint8_t data[9];
		for (uint8_t i = 0; i < 9; i++) // On lit le scratchpad
			data[i] = read_byte();       // Et on stock les octets reçus

		// Calcul de la température en degré Celsius
		return ((data[1] << 8) | data[0]) * 0.0625;
	}

}
