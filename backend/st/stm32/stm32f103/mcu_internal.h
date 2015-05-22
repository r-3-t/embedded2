#pragma once

#include <stm32f10x.h>

namespace stm32f103
{
constexpr unsigned int PORT_PIN_TO_ID(unsigned short port, unsigned short pin) { return ((port << 16) | pin ); }
constexpr unsigned short ID_TO_PORT(unsigned int id) { return (id >> 16); }
constexpr unsigned short ID_TO_PIN(unsigned int id) { return (id & 0xFFFF); }

constexpr unsigned int __GPIOA	= 0x0001;
constexpr unsigned int __GPIOB	= 0x0002;
constexpr unsigned int __GPIOC 	= 0x0004;
}

enum port
{
	PA0 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOA, 0x0001),
	PA1 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOA, 0x0002),
	PA2 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOA, 0x0004),
	PA3 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOA, 0x0008),
	PA4 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOA, 0x0010),
	PA5 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOA, 0x0020),
	PA6 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOA, 0x0040),
	PA7 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOA, 0x0080),
	PA8 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOA, 0x0100),
	PA9 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOA, 0x0200),
	PA10 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOA, 0x0400),
	PA11 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOA, 0x0800),
	PA12 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOA, 0x1000),
	PA13 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOA, 0x2000),
	PA14 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOA, 0x4000),
	PA15 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOA, 0x8000),

	PB0 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOB, 0x0001),
	PB1 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOB, 0x0002),
	PB2 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOB, 0x0004),
	PB3 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOB, 0x0008),
	PB4 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOB, 0x0010),
	PB5 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOB, 0x0020),
	PB6 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOB, 0x0040),
	PB7 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOB, 0x0080),
	PB8 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOB, 0x0100),
	PB9 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOB, 0x0200),
	PB10 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOB, 0x0400),
	PB11 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOB, 0x0800),
	PB12 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOB, 0x1000),
	PB13 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOB, 0x2000),
	PB14 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOB, 0x4000),
	PB15 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOB, 0x8000),

	PC0 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOC, 0x0001),
	PC1 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOC, 0x0002),
	PC2 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOC, 0x0004),
	PC3 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOC, 0x0008),
	PC4 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOC, 0x0010),
	PC5 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOC, 0x0020),
	PC6 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOC, 0x0040),
	PC7 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOC, 0x0080),
	PC8 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOC, 0x0100),
	PC9 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOC, 0x0200),
	PC10 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOC, 0x0400),
	PC11 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOC, 0x0800),
	PC12 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOC, 0x1000),
	PC13 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOC, 0x2000),
	PC14 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOC, 0x4000),
	PC15 	= stm32f103::PORT_PIN_TO_ID(stm32f103::__GPIOC, 0x8000),
};

// this structure is a private member of gpio class
struct gpio_mcu_internal
{
	GPIO_TypeDef* 	GPIOx;
	unsigned int 	pin;
	port 			p;
};

// this structure is a private member of uart class
struct uart_mcu_internal
{
	USART_TypeDef* 	USARTx;
	unsigned int	Id;
};	


