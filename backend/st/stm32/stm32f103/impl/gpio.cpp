#include <hal/gpio.h>

#include "pinout.h"

#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

namespace gpio
{

gpio::gpio(port Id)
{
	used_pinout::register_port(Id);
	_internal.p = Id;
	_internal.pin  = stm32f103::ID_TO_PIN(Id);

	uint32_t RCC_APB2Periph;
	switch (stm32f103::ID_TO_PORT(Id))
	{
		case stm32f103::__GPIOA: _internal.GPIOx = GPIOA; RCC_APB2Periph = RCC_APB2Periph_GPIOA; break;
		case stm32f103::__GPIOB: _internal.GPIOx = GPIOB; RCC_APB2Periph = RCC_APB2Periph_GPIOB; break;
		case stm32f103::__GPIOC: _internal.GPIOx = GPIOC; RCC_APB2Periph = RCC_APB2Periph_GPIOC; break;
	}

	RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);
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

void gpio::set_as_digital_input(InputMode mode)
{
	GPIO_InitTypeDef GPIO_InitDef;
	GPIO_StructInit(&GPIO_InitDef);

	GPIO_InitDef.GPIO_Pin = _internal.pin;
	switch (mode)
	{
		case PullUp		:	GPIO_InitDef.GPIO_Mode = GPIO_Mode_IPU; break;
		case PullDown	:	GPIO_InitDef.GPIO_Mode = GPIO_Mode_IPD; break;
		case NoPull		:	GPIO_InitDef.GPIO_Mode = GPIO_Mode_IN_FLOATING; break;
	}
	//50MHz pin speed
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
	//Initialize pins
	GPIO_Init(_internal.GPIOx, &GPIO_InitDef);
}

void gpio::set_as_analog_input()
{
	GPIO_InitTypeDef GPIO_InitDef;
	GPIO_StructInit(&GPIO_InitDef);

	GPIO_InitDef.GPIO_Pin = _internal.pin;
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_AIN;

	//50MHz pin speed
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
	//Initialize pins
	GPIO_Init(_internal.GPIOx, &GPIO_InitDef);
}

void gpio::set_as_digital_output(OutputMode mode)
{
	GPIO_InitTypeDef GPIO_InitDef;
	GPIO_StructInit(&GPIO_InitDef);
	GPIO_InitDef.GPIO_Pin = _internal.pin;

	switch (mode)
	{
		case PushPull	: GPIO_InitDef.GPIO_Mode = GPIO_Mode_Out_PP; break;
		case OpenDrain	: GPIO_InitDef.GPIO_Mode = GPIO_Mode_Out_OD; break;		
	}

	//50MHz pin speed
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
	//Initialize pins
	GPIO_Init(_internal.GPIOx, &GPIO_InitDef);
}

uint8_t gpio::gpio::get_input_value()
{
	return 0;
}

}
