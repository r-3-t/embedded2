#pragma once

#include <hal/uart.h>


#if defined STM32F407

#	include "stm32f4xx_usart.h"

#elif defined STM32F103

#	include "stm32f10x_usart.h"

#else

#	error "Undefined mcu"

#endif

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

}
