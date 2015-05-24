#pragma once

#include "mcu_internal.h"

namespace i2c
{
	struct Configuration
	{
		typedef enum {Master, Slave} Mode_t;
		Mode_t Mode;                /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
											This parameter can be a value of @ref USART_Mode */

		typedef enum {StandardMode = 100000, FastMode = 400000} ClockSpeed_t;
		ClockSpeed_t ClockSpeed;

		typedef enum {_7_bits, _10_bits} AddressMode_t;
		AddressMode_t AddressMode;

		typedef enum {Enable, Disable} AcknowledgementMode_t;


		static Configuration _Master()
		{
			return {Master, StandardMode, _7_bits, Enable};
		}

		static Configuration _Slave()
		{
			return {Slave, StandardMode, _7_bits, Enable};
		}
	};

	class i2c
	{
	public:
		i2c(unsigned int id);

		void init(i2c::config config), callback;

		void send(const char car);

	private:
		i2c_mcu_internal _internal;
		i2c_receive_callback _receive_callback;
	};
}
