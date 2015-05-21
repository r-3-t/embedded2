#include <hal/gpio.h>

#include <mcu_internal.h>

#if defined STM32F407

int main()
{
	gpio::gpio gpio1(PD12);
	gpio1.set_as_digital_output(gpio::PushPull);
	gpio1.on();

	gpio::gpio gpio2(PD13);
	gpio2.set_as_digital_output(gpio::PushPull);
	gpio2.on();


	gpio::gpio gpio3(PD14);
	gpio3.set_as_digital_output(gpio::PushPull);
	gpio3.on();


	gpio::gpio gpio4(PD15);
	gpio4.set_as_digital_output(gpio::PushPull);
	gpio4.on();


	while(1) {};

	return 0;
}

#elif defined STM32F103

int main()
{
	gpio::gpio gpio1(PC13);
	gpio1.set_as_digital_output(gpio::PushPull);
	gpio1.on();


	while(1) {};

	return 0;
}

#else

#error "No known mcu for this example"

#endif

