#include <hal/gpio.h>

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#include "mcu_internal.h"
#include "pinout.h"

namespace gpio
{

gpio::gpio(port Id)
{
	used_pinout::register_port(Id);

	_internal.p = Id;

	unsigned int Gpio_RCC_AHB1Periph = 0;
	switch (stm32f407::ID_TO_PORT(Id))
	{
		case stm32f407::__GPIOA: _internal.GPIOx = GPIOA; Gpio_RCC_AHB1Periph = RCC_AHB1Periph_GPIOA; break;
		case stm32f407::__GPIOB: _internal.GPIOx = GPIOB; Gpio_RCC_AHB1Periph = RCC_AHB1Periph_GPIOB; break;
		case stm32f407::__GPIOC: _internal.GPIOx = GPIOC; Gpio_RCC_AHB1Periph = RCC_AHB1Periph_GPIOC; break;
		case stm32f407::__GPIOD: _internal.GPIOx = GPIOD; Gpio_RCC_AHB1Periph = RCC_AHB1Periph_GPIOD; break;
		case stm32f407::__GPIOE: _internal.GPIOx = GPIOE; Gpio_RCC_AHB1Periph = RCC_AHB1Periph_GPIOE; break;
		case stm32f407::__GPIOF: _internal.GPIOx = GPIOF; Gpio_RCC_AHB1Periph = RCC_AHB1Periph_GPIOF; break;
		case stm32f407::__GPIOG: _internal.GPIOx = GPIOG; Gpio_RCC_AHB1Periph = RCC_AHB1Periph_GPIOG; break;
		case stm32f407::__GPIOH: _internal.GPIOx = GPIOH; Gpio_RCC_AHB1Periph = RCC_AHB1Periph_GPIOH; break;
		case stm32f407::__GPIOI: _internal.GPIOx = GPIOI; Gpio_RCC_AHB1Periph = RCC_AHB1Periph_GPIOI; break;
		case stm32f407::__GPIOJ: _internal.GPIOx = GPIOJ; Gpio_RCC_AHB1Periph = RCC_AHB1Periph_GPIOJ; break;
		default : while (1);
	}

	_internal.pin  = stm32f407::ID_TO_PIN(Id);

	//Enable clock for selected GPIO
	RCC_AHB1PeriphClockCmd(Gpio_RCC_AHB1Periph, ENABLE);

	GPIO_InitTypeDef GPIO_InitDef;
	GPIO_InitDef.GPIO_Pin = _internal.pin;
	
}

gpio::~gpio()
{
	used_pinout::unregister_port(_internal.p);
}

void gpio::on()
{
	GPIO_SetBits(_internal.GPIOx, _internal.pin);
}

void gpio::high()
{
	GPIO_SetBits(_internal.GPIOx, _internal.pin);
}

void gpio::off()
{
	GPIO_ResetBits(_internal.GPIOx, _internal.pin);
}

void gpio::low()
{
	GPIO_ResetBits(_internal.GPIOx, _internal.pin);
}

void gpio::set_as_digital_input(InputMode mode)
{
	GPIO_InitTypeDef GPIO_InitDef;
	GPIO_StructInit(&GPIO_InitDef);

	GPIO_InitDef.GPIO_Pin = _internal.pin;
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_IN;
	switch (mode)
	{
		case PullUp		:	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_UP; break;
		case PullDown	:	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_DOWN; break;
		case NoPull		:	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL; break;
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
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_AN;

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
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;

	switch (mode)
	{
		case PushPull	: GPIO_InitDef.GPIO_OType = GPIO_OType_PP; break;
		case OpenDrain	: GPIO_InitDef.GPIO_OType = GPIO_OType_OD; break;		
	}

	//50MHz pin speed
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
	//Initialize pins
	GPIO_Init(_internal.GPIOx, &GPIO_InitDef);
}

uint8_t gpio::get_input_value()
{
	return ((_internal.GPIOx)->IDR & (_internal.pin)) == 0 ? 0 : 1;
}

}
