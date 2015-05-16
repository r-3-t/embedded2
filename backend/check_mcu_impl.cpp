#include <hal/uart.h>
#include <hal/gpio.h>

void check_uart()
{
	uart::uart uart1;

	uart1.init(1, uart::config::_9600_8_N_1(), nullptr);

	uart1.send ("Hello from uart\n");
}

void check_gpio()
{
	gpio::gpio gpio1(PA0, gpio::NoPull);

	gpio1.on();
	gpio1.off();
	gpio1.high();
	gpio1.low();
}

int main (int argc, char** argv)
{
	check_uart();

	check_gpio();

	while (true);
	return 0;

}
