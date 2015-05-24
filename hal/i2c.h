#pragma once

#include "mcu_internal.h"

namespace i2c
{
	struct Configuration
	{
		typedef enum {StandardMode = 100000, FastMode = 400000} ClockSpeed_t;
		ClockSpeed_t ClockSpeed;

		typedef enum {_7_bits, _10_bits} AddressMode_t;
		AddressMode_t AddressMode;

		typedef enum {Enable, Disable} AcknowledgementMode_t;


		static Configuration default()
		{
			return {StandardMode, _7_bits, Enable};
		}
	};

	class i2c
	{
	public:
		typedef void (*receive_callback)(const uint8_t c);
		typedef void (*request_callback)();

		i2c(unsigned int id);

		void set_as_master(i2c::config config, receive_callback callback);
		void set_as_slave(i2c::config config, receive_callback callback, request_callback request_callback);

		void send(const char car);
		void send(const char* data)
		{
			while (*data != 0)
			{
				send(*data);
				++data;
			}
		}
		void send(const unsigned char* data, unsigned int length)
		{
			for (unsigned int i = 0; i < length; i++)
				send(data[i]);
		}

	private:
		i2c_mcu_internal _internal;
		receive_callback _receive_callback;
		request_callback _request_callback;
	};
}
