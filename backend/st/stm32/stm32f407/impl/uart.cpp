#include <hal/uart.h>

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "misc.h"

#include "mcu_internal.h"

namespace uart
{

inline static uint32_t conf_2_baudrate(config::Baudrate_t baudrate)
{
	switch (baudrate)
	{
		case config::_9600	:	return 9600; 	break;
		case config::_19200	:	return 19200;	break;
		case config::_38400	:	return 38400;	break;
		case config::_57600	:	return 57600;	break;
		case config::_115200 :	return 115200;	break;
	}

	return (uint32_t)-1;
}

inline static uint16_t	conf_2_WordLength(config::WordLength_t word_length)
{
	switch (word_length)
	{
		case config::_8b:	return USART_WordLength_8b;
		case config::_9b:	return USART_WordLength_9b;
	}

	return (uint16_t)-1;
}

inline static uint16_t	conf_2_StopBits(config::StopBit_t StopBits)
{
	switch (StopBits)
	{
		case config::_1:		return USART_StopBits_1;
		/*case uc::config::_0_5:	return USART_StopBits_0_5;*/
		case config::_2:		return USART_StopBits_2;
		case config::_1_5:	return USART_StopBits_1_5;
	}

	return (uint16_t)-1;
}

inline static uint16_t	conf_2_Parity(config::Parity_t Parity)
{
	switch (Parity)
	{
		case config::no:		return USART_Parity_No;
		case config::even:	return USART_Parity_Even;
		case config::odd:	return USART_Parity_Odd;
	}

	return (uint16_t)-1;	
}

inline static uint16_t	conf_2_Mode(config::Mode_t Mode)
{
	switch (Mode)
	{
		case config::Rx:		return USART_Mode_Rx;
		case config::Tx:		return USART_Mode_Tx;
		case config::Rx_Tx:	return (USART_Mode_Rx | USART_Mode_Tx);
	}

	return (uint16_t)-1;		
}

inline static uint16_t	conf_2_HardwareFlowControl(config::HardwareFlowControl_t HardwareFlowControl)
{
	switch (HardwareFlowControl)
	{
		case config::None:		return USART_HardwareFlowControl_None;
		case config::Rts:		return USART_HardwareFlowControl_RTS;
		case config::Cts:		return USART_HardwareFlowControl_CTS;
		case config::Rts_Cts:	return USART_HardwareFlowControl_RTS_CTS;
	}	

	return (uint16_t)-1;
}

uart::uart_callback TabCallback[2];

extern "C"
{
	void USART1_IRQHandler(void)
	{
			// check if the USART1 receive interrupt flag was set
		if( USART_GetITStatus(USART1, USART_IT_RXNE) ){
			
			static uint8_t cnt = 0; // this counter is used to determine the string length
			char t = USART1->DR; // the character from the USART1 data register is saved in t
			
			TabCallback[0](t);
		}	
	}

	void USART2_IRQHandler(void)
	{
			// check if the USART1 receive interrupt flag was set
		if( USART_GetITStatus(USART2, USART_IT_RXNE) ){
			
			static uint8_t cnt = 0; // this counter is used to determine the string length
			char t = USART2->DR; // the character from the USART1 data register is saved in t
			
			TabCallback[1](t);
		}	
	}

}

uart::uart() : _callback(nullptr)
{
}

void uart::init(unsigned int Id, config configuration, uart_callback callback)
{
	_callback = callback;

	// here perform the initialisation
	USART_InitTypeDef		USART_InitStruct; // this is for the USART2 initilization
	NVIC_InitTypeDef		NVIC_InitStructure; // this is used to configure the NVIC (nested vector interrupt controller)

	GPIO_TypeDef* 	GPIOx;
	uint32_t		GPIO_Pin_Rx, GPIO_Pin_Tx;			// the selected pin
	uint16_t		GPIO_PinSource_Tx;
	uint16_t		GPIO_PinSource_Rx;
	uint8_t			GPIO_AF_Tx;
	uint8_t			GPIO_AF_Rx;
	uint8_t			GPIO_AF;

	uint32_t		RCC_AHBPeriph_GPIOX;
	uint32_t		RCC_APB2Periph_USARTx;

	switch (Id)
	{
		case 1: _internal.USARTx = USART1;
				GPIOx								= GPIOB;
				GPIO_Pin_Tx							= GPIO_Pin_6;
				GPIO_Pin_Rx							= GPIO_Pin_7;
				GPIO_PinSource_Tx					= GPIO_PinSource6;
				GPIO_PinSource_Rx					= GPIO_PinSource7;
				GPIO_AF								= GPIO_AF_USART1;
				RCC_AHBPeriph_GPIOX					= RCC_AHB1Periph_GPIOB;
				RCC_APB2Periph_USARTx				= RCC_APB2Periph_USART1;
				NVIC_InitStructure.NVIC_IRQChannel	= USART1_IRQn;
				TabCallback[0] = callback;

				break;
		case 2: _internal.USARTx = USART2;
				GPIOx								= GPIOA;
				GPIO_Pin_Tx							= GPIO_Pin_2;
				GPIO_Pin_Rx							= GPIO_Pin_3;
				GPIO_PinSource_Tx					= GPIO_PinSource2;
				GPIO_PinSource_Rx					= GPIO_PinSource3;
				GPIO_AF								= GPIO_AF_USART2;
				RCC_AHBPeriph_GPIOX					= RCC_AHB1Periph_GPIOA;
				RCC_APB2Periph_USARTx				= RCC_APB1Periph_USART2;
				NVIC_InitStructure.NVIC_IRQChannel	= USART2_IRQn;
				TabCallback[1] = callback;


				break;				break;
		case 3: _internal.USARTx = USART3;
				break;
		case 4: _internal.USARTx = UART4;
				break;
		case 5: _internal.USARTx = UART5;
				break;
		case 6: _internal.USARTx = USART6;
				break;
		default : _internal.USARTx = nullptr;
	}

	//GPIO
	RCC_AHB1PeriphClockCmd(RCC_AHBPeriph_GPIOX, ENABLE);
	//USART
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USARTx, ENABLE);


	GPIO_InitTypeDef GPIO_InitStructure;

	/* RX Pin and TX Pin */
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Tx | GPIO_Pin_Rx;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOx, &GPIO_InitStructure);


	GPIO_PinAFConfig(GPIOx, GPIO_PinSource_Tx, GPIO_AF);
	GPIO_PinAFConfig(GPIOx, GPIO_PinSource_Rx, GPIO_AF);


	USART_InitStruct.USART_BaudRate				= conf_2_baudrate(configuration.baudRate);       // the baudrate is set to the value we passed into this init function
	USART_InitStruct.USART_WordLength			= conf_2_WordLength(configuration.WordLength);// we want the data frame size to be 8 bits (standard)
	USART_InitStruct.USART_StopBits				= conf_2_StopBits(configuration.StopBits);   // we want 1 stop bit (standard)
	USART_InitStruct.USART_Parity				= conf_2_Parity(configuration.Parity);    // we don't want a parity bit (standard)
	USART_InitStruct.USART_HardwareFlowControl	= conf_2_HardwareFlowControl(configuration.HardwareFlowControl); // we don't want flow control (standard)
	USART_InitStruct.USART_Mode					= conf_2_Mode(configuration.Mode); // we want to enable the transmitter and the receiver
	USART_Init(_internal.USARTx, &USART_InitStruct);          // again all the properties are passed to the USART_Init function which takes care of all the bit setting

	USART_ITConfig(_internal.USARTx, USART_IT_RXNE, ENABLE);

	//NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQHandler;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(_internal.USARTx, ENABLE);
}

uart::~uart()
{

}

void uart::send(unsigned char data)
{
	while ((_internal.USARTx->SR & USART_FLAG_TC) == (uint16_t) RESET) {}
	
	_internal.USARTx->DR = (data & (uint16_t) 0x01FF);
}

void uart::send(const char* data)
{
	while (*data != 0)
	{
		send(*data);
		++data;
	}
}

void uart::send(const unsigned char* data, unsigned int length)
{
	for (unsigned int i = 0; i < length; i++)
		send(data[i]);
}

}
