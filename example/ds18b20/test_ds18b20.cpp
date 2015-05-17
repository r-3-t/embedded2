#include <hal/uart.h>
#include <hal/time.h>

#include <stdio.h>

#include <driver/ds18b20/ds18b20.h>

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

	// init uart1
	uart1.init(1, uart::config::_9600_8_N_1(), nullptr);

	printf ("start ds18b20 sensor\n");

	ds18b20::ds18b20 test_ds18b20(PB1);

	while(1)
	{
		time::msleep(1000);
		printf ("temperature : %f\n", test_ds18b20.get_temperature());
	};

	return 0;
}


