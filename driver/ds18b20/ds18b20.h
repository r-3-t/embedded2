#pragma once

#include <driver/one_wire/one_wire.h>
#include <hal/gpio.h>
#include <cstdint>

namespace ds18b20
{

	class ds18b20 : protected one_wire::one_wire
	{
	public:
		ds18b20(port Id);
		~ds18b20();


		float get_temperature();

	private:
		uint8_t _ROM_NO[8];
	};

}
