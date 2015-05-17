#pragma once

#include "hal/gpio.h"

namespace one_wire
{
	/* OneWire commands */
	const uint8_t CMD_RSCRATCHPAD	= 0xBE;
	const uint8_t CMD_WSCRATCHPAD	= 0x4E;
	const uint8_t CMD_CPYSCRATCHPAD	= 0x48;
	const uint8_t CMD_RECEEPROM		= 0xB8;
	const uint8_t CMD_RPWRSUPPLY	= 0xB4;
	const uint8_t CMD_SEARCHROM		= 0xF0;
	const uint8_t CMD_READROM		= 0x33;
	const uint8_t CMD_MATCHROM		= 0x55;
	const uint8_t CMD_SKIPROM		= 0xCC;

	uint8_t crc8( uint8_t *addr, uint8_t len);

	struct search_context
	{
		uint8_t LastDiscrepancy;		/*!< Search private */
		uint8_t LastFamilyDiscrepancy;	/*!< Search private */
		bool SearchTerminated;		/*!< Search private */
	};

	class one_wire : protected gpio::gpio
	{
	public:
		one_wire(port Id);
		~one_wire();

		// true meens ok, false : error
		bool reset();

		uint8_t read_bit();
		uint8_t read_byte();

		void write_bit(uint8_t);
		void write_byte(uint8_t);

		void select (uint8_t ROM_NO[8]);

		void init_search(search_context* pSearchCtx);
		uint8_t get_next_periph(search_context* pSearchCtx, uint8_t ROM_NO[8]);

	private:
		
	};

}
