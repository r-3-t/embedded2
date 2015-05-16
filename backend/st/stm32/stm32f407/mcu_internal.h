#pragma once

#include <stm32f4xx.h>

namespace stm32f407
{
constexpr unsigned int PORT_PIN_TO_ID(unsigned short port, unsigned short pin) { return ((port << 16) | pin ); }
constexpr unsigned short ID_TO_PORT(unsigned int id) { return (id >> 16); }
constexpr unsigned short ID_TO_PIN(unsigned int id) { return (id & 0xFFFF); }

constexpr unsigned int __GPIOA	= 0x0001;
constexpr unsigned int __GPIOB	= 0x0002;
constexpr unsigned int __GPIOC 	= 0x0004;
constexpr unsigned int __GPIOD 	= 0x0008;
constexpr unsigned int __GPIOE 	= 0x0010;
constexpr unsigned int __GPIOF 	= 0x0020;
constexpr unsigned int __GPIOG 	= 0x0040;
constexpr unsigned int __GPIOH 	= 0x0080;
constexpr unsigned int __GPIOI 	= 0x0100;
constexpr unsigned int __GPIOJ 	= 0x0200;
}

enum port
{
	PA0 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOA, 0x0001),
	PA1 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOA, 0x0002),
	PA2 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOA, 0x0004),
	PA3 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOA, 0x0008),
	PA4 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOA, 0x0010),
	PA5 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOA, 0x0020),
	PA6 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOA, 0x0040),
	PA7 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOA, 0x0080),
	PA8 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOA, 0x0100),
	PA9 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOA, 0x0200),
	PA10 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOA, 0x0400),
	PA11 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOA, 0x0800),
	PA12 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOA, 0x1000),
	PA13 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOA, 0x2000),
	PA14 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOA, 0x4000),
	PA15 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOA, 0x8000),

	PB0 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOB, 0x0001),
	PB1 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOB, 0x0002),
	PB2 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOB, 0x0004),
	PB3 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOB, 0x0008),
	PB4 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOB, 0x0010),
	PB5 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOB, 0x0020),
	PB6 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOB, 0x0040),
	PB7 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOB, 0x0080),
	PB8 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOB, 0x0100),
	PB9 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOB, 0x0200),
	PB10 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOB, 0x0400),
	PB11 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOB, 0x0800),
	PB12 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOB, 0x1000),
	PB13 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOB, 0x2000),
	PB14 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOB, 0x4000),
	PB15 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOB, 0x8000),

	PC0 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOC, 0x0001),
	PC1 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOC, 0x0002),
	PC2 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOC, 0x0004),
	PC3 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOC, 0x0008),
	PC4 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOC, 0x0010),
	PC5 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOC, 0x0020),
	PC6 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOC, 0x0040),
	PC7 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOC, 0x0080),
	PC8 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOC, 0x0100),
	PC9 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOC, 0x0200),
	PC10 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOC, 0x0400),
	PC11 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOC, 0x0800),
	PC12 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOC, 0x1000),
	PC13 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOC, 0x2000),
	PC14 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOC, 0x4000),
	PC15 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOC, 0x8000),

	PD0 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOD, 0x0001),
	PD1 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOD, 0x0002),
	PD2 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOD, 0x0004),
	PD3 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOD, 0x0008),
	PD4 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOD, 0x0010),
	PD5 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOD, 0x0020),
	PD6 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOD, 0x0040),
	PD7 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOD, 0x0080),
	PD8 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOD, 0x0100),
	PD9 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOD, 0x0200),
	PD10 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOD, 0x0400),
	PD11 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOD, 0x0800),
	PD12 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOD, 0x1000),
	PD13 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOD, 0x2000),
	PD14 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOD, 0x4000),
	PD15 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOD, 0x8000),

	PE0 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOE, 0x0001),
	PE1 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOE, 0x0002),
	PE2 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOE, 0x0004),
	PE3 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOE, 0x0008),
	PE4 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOE, 0x0010),
	PE5 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOE, 0x0020),
	PE6 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOE, 0x0040),
	PE7 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOE, 0x0080),
	PE8 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOE, 0x0100),
	PE9 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOE, 0x0200),
	PE10 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOE, 0x0400),
	PE11 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOE, 0x0800),
	PE12 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOE, 0x1000),
	PE13 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOE, 0x2000),
	PE14 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOE, 0x4000),
	PE15 	= stm32f407::PORT_PIN_TO_ID(stm32f407::__GPIOE, 0x8000),
};

struct gpio_mcu_internal
{
	GPIO_TypeDef* 	GPIOx;
	unsigned int 	pin;
	port 			p;
};

struct uart_mcu_internal
{
	USART_TypeDef* 	USARTx;
	unsigned int	Id;
};	


