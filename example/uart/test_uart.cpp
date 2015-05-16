#include <hal/uart.h>


void callback (const uint8_t c);

//------------------------------------------------------------------------------

uart::uart uart1;

//------------------------------------------------------------------------------

void callback (const uint8_t c)
{
	uart1.send(&c, sizeof(c));
	uart1.send("\r\n");
}


int main (int argc, char** argv)
{
	uart1.init(1, uart::config::_9600_8_N_1(), callback);

	uart1.send ("Hello from uart\n");

	while (true);
	return 0;
}
