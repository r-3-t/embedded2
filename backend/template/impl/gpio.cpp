#include <hal/gpio.h>



namespace gpio
{

gpio::gpio(port Id, InputMode input, OutputMode output, GpioMode mode)
{
	used_pinout::register_port(Id);
}

gpio::~gpio()
{
	used_pinout::unregister_port(_internal.p);
}

void gpio::on()
{

}

void gpio::high()
{

}

void gpio::off()
{

}

void gpio::low()
{

}

void gpio::set_gpio_mode(GpioMode mode)
{

}

uint8_t gpio::get_input_value()
{

}

}
