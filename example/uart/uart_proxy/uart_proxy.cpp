#include <hal/uart.h>


//------------------------------------------------------------------------------

uart::uart uart1;
uart::uart uart2;

//------------------------------------------------------------------------------

void callback_uart1 (const uint8_t c)
{
	uart2.send(c);
}

void callback_uart2 (const uint8_t c)
{
	uart1.send(c);
}

int main (int argc, char** argv)
{
	uart1.init(1, uart::config::_9600_8_N_1(), callback_uart1);
	uart2.init(2, uart::config::_9600_8_N_1(), callback_uart2);


	while (true);
	return 0;
}
