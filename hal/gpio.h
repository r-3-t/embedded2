#include <mcu_internal.h>

namespace gpio
{

class gpio
{
public:
	gpio(port Id);

	~gpio();

	void on();
	void high();

	void off();
	void low();



private:
	gpio_mcu_internal _internal;
};
}
