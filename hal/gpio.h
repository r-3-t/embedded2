#pragma once

#include <mcu_internal.h>
#include <cstdint>

namespace gpio
{

enum InputMode
{
	PullUp		= 0x00,
	PullDown	= 0x01,
	NoPull		= 0x02
};

enum OutputMode
{
	PushPull	= 0x00,
	OpenDrain	= 0x01,
};

enum GpioMode
{
	Input		= 0x00,
	Output		= 0x01,
	AnalogInput	= 0x03,
};

class gpio
{
public:
	gpio(port Id);

	~gpio();

	void on();
	void high();

	void off();
	void low();

	void set_as_digital_input(InputMode mode);
	void set_as_analog_input();

	void set_as_digital_output(OutputMode mode);

	uint8_t get_input_value();

private:
	gpio_mcu_internal _internal;
};
}
