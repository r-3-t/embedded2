#include <hal/uart.h>
#include <array>

#include "stm32/common/uart_conf.h"

#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "misc.h"


#include "pinout.h"

namespace uart
{

std::array<uart::uart_callback, 2> TabCallback { {nullptr, nullptr} };

extern "C"
{
	void USART1_IRQHandler(void)
	{
			// check if the USART1 receive interrupt flag was set
		if( USART_GetITStatus(USART1, USART_IT_RXNE) ){
			
			static uint8_t cnt = 0; // this counter is used to determine the string length
			char t = USART1->DR; // the character from the USART1 data register is saved in t
			
			if (TabCallback[0] != nullptr)
				TabCallback[0](t);
		}	
	}

	void USART2_IRQHandler(void)
	{
			// check if the USART1 receive interrupt flag was set
		if( USART_GetITStatus(USART2, USART_IT_RXNE) ){
			
			static uint8_t cnt = 0; // this counter is used to determine the string length
			char t = USART2->DR; // the character from the USART1 data register is saved in t
			
			if (TabCallback[1] != nullptr)
				TabCallback[1](t);
		}	
	}

}


uart::uart() : _callback(nullptr)
{
}

void uart::init(unsigned int Id, config configuration, uart_callback callback)
{
	// here perform the initialisation
	USART_InitTypeDef		USART_InitStruct; // this is for the USART2 initilization
	NVIC_InitTypeDef		NVIC_InitStructure; // this is used to configure the NVIC (nested vector interrupt controller)


	// the gpio used
	GPIO_TypeDef* 	GPIOx;
	uint32_t		GPIO_Pin_Rx, GPIO_Pin_Tx;			// the selected pin
	uint16_t		GPIO_PinSource_Tx;
	uint16_t		GPIO_PinSource_Rx;
	uint8_t			GPIO_AF_Tx;
	uint8_t			GPIO_AF_Rx;
	uint8_t			GPIO_AF;

	_callback = callback;

	_internal.Id = Id;
	switch (Id)
	{
		case 1: 
				used_pinout::register_port(PA9);
				used_pinout::register_port(PA10);
				_internal.USARTx = USART1;
				GPIOx						= GPIOA;
				GPIO_Pin_Tx					= GPIO_Pin_9;
				GPIO_Pin_Rx					= GPIO_Pin_10;
				
				//GPIO
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
				//USART
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

				NVIC_InitStructure.NVIC_IRQChannel	= USART1_IRQn;
				TabCallback[0] = callback;

				break;
		case 2: 
				used_pinout::register_port(PA2);
				used_pinout::register_port(PA3);
				_internal.USARTx = USART2;
				GPIOx						= GPIOA;
				GPIO_Pin_Tx					= GPIO_Pin_2;
				GPIO_Pin_Rx					= GPIO_Pin_3;
				
				//GPIO
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
				//USART
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

				NVIC_InitStructure.NVIC_IRQChannel	= USART2_IRQn;
				TabCallback[1] = callback;


				break;				break;

		default : 
					while (true) {}
					_internal.USARTx = nullptr;
	}
	GPIO_InitTypeDef GPIO_InitStructure;
			
	/* TX Pin */
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Tx;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx, &GPIO_InitStructure);

	/* RX Pin */
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Rx;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx, &GPIO_InitStructure);

	
	USART_InitStruct.USART_BaudRate = conf_2_baudrate(configuration.baudRate);       // the baudrate is set to the value we passed into this init function
	USART_InitStruct.USART_WordLength = conf_2_WordLength(configuration.WordLength);// we want the data frame size to be 8 bits (standard)
	USART_InitStruct.USART_StopBits = conf_2_StopBits(configuration.StopBits);   // we want 1 stop bit (standard)
	USART_InitStruct.USART_Parity = conf_2_Parity(configuration.Parity);    // we don't want a parity bit (standard)
	USART_InitStruct.USART_HardwareFlowControl = conf_2_HardwareFlowControl(configuration.HardwareFlowControl); // we don't want flow control (standard)
	USART_InitStruct.USART_Mode = conf_2_Mode(configuration.Mode); // we want to enable the transmitter and the receiver
	USART_Init(_internal.USARTx, &USART_InitStruct);          // again all the properties are passed to the USART_Init function which takes care of all the bit setting
	
	USART_ITConfig(_internal.USARTx, USART_IT_RXNE, ENABLE);


	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(_internal.USARTx, ENABLE);
}

uart::~uart()
{
	switch (_internal.Id)
	{
		case 1: 
				used_pinout::unregister_port(PA9);
				used_pinout::unregister_port(PA10);
		case 2: 
				used_pinout::unregister_port(PA2);
				used_pinout::unregister_port(PA3);
	}
}

void uart::send(unsigned char data)
{
	while ((_internal.USARTx->SR & USART_FLAG_TC) == (uint16_t) RESET) {}
		_internal.USARTx->DR = (data & (uint16_t) 0x01FF);
}


}
