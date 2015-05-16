#include <hal/gpio.h>

#include <mcu_internal.h>


int main()
{
	gpio::gpio gpio1(PD12);

	gpio1.on();

	gpio::gpio gpio2(PD13);
	gpio2.on();


	gpio::gpio gpio3(PD14);
	gpio3.on();


	gpio::gpio gpio4(PD15);
	gpio4.on();


	while(1) {};

	return 0;
}


