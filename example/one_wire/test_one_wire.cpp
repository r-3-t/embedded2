#include <hal/uart.h>
#include <hal/time.h>

#include <stdio.h>

#include <driver/one_wire/one_wire.h>

#include <mcu_internal.h>

uart::uart uart1;

//------------------------------------------------------------------------------

extern "C"
{
void write_stdout (const unsigned char* ptr, unsigned int len)
{
	uart1.send(ptr, len);
}
}


//------------------------------------------------------------------------------

int main()
{
	one_wire::one_wire test_one_wire(PB1);
	

	// init uart1
	uart1.init(1, uart::config::_9600_8_N_1(), nullptr);

	// wait 1s
	time::msleep(1000);

	printf ("Test One Wire \n");

	bool ok = test_one_wire.reset();

	if (ok)
		printf ("reset ok\n");
	else
		printf ("reset failed\n");

	one_wire::search_context search_ctx;
	test_one_wire.init_search(&search_ctx);

	unsigned int nCount = 0;
	uint8_t ROM_NO[8];             /*!< 8-bytes address of last search device */
	while (test_one_wire.get_next_periph(&search_ctx, ROM_NO))
	{
		printf("Device %d: %02X %02X %02X %02X %02X %02X %02X %02X (CRC : %02X)\n",
				         nCount+1,
				         ROM_NO[7],ROM_NO[6],
				         ROM_NO[5],ROM_NO[4],
				         ROM_NO[3],ROM_NO[2],
				         ROM_NO[1],ROM_NO[0], one_wire::crc8(ROM_NO, 7));
		++nCount;
	}

	printf("DeviceCount: %d\n", nCount);

	// test_one_wire.reset();
	// test_one_wire.select(ROM_NO);

	// printf ("sensor selected\n");

	// test_one_wire.write_byte(0x44);      // On lance une prise de mesure de température
	// time::usleep(800);             		// Et on attend la fin de la mesure

	// test_one_wire.reset();             // On reset le bus 1-Wire
	// test_one_wire.select(ROM_NO);        // On sélectionne le DS18B20
	// test_one_wire.write_byte(0xBE);         // On envoie une demande de lecture du scratchpad

	// time::usleep(10);
	// uint8_t data[9];
	// for (uint8_t i = 0; i < 9; i++) // On lit le scratchpad
	// 	data[i] = test_one_wire.read_byte();       // Et on stock les octets reçus

	// printf ("scratchpad : ");
	// for (uint8_t i = 0; i < 9; i++) // On lit le scratchpad
	// 	printf ("%02X ", data[i]);
	// printf ("\n");

	// // Calcul de la température en degré Celsius
	// float temp = ((data[1] << 8) | data[0]) * 0.0625;

	// printf ("temperature : %f\n", temp);

	while(1) {};

	return 0;
}


