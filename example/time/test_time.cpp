#include <hal/uart.h>
#include <hal/time.h>

#include <stdio.h>

//------------------------------------------------------------------------------

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

int main (int argc, char** argv)
{
	uart1.init(1, uart::config::_9600_8_N_1(), nullptr);

	uint32_t seconds = 0; 
	while (true)
	{
		time::msleep(1000);
		printf ("%08d seconds since boot\n", seconds);
		seconds++;
	}
	return 0;
}
