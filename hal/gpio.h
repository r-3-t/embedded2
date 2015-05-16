#pragma once

#include <mcu_internal.h>

namespace gpio
{

enum pullup_pulldown
{
  PullUp	= 0x00,
  PullDown	= 0x01,
  NoPull	= 0x02
};

class gpio
{
public:
	gpio(port Id, pullup_pulldown config);

	~gpio();

	void on();
	void high();

	void off();
	void low();



private:
	gpio_mcu_internal _internal;
};
}
