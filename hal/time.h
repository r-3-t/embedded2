#pragma once

#include <cstdint>

namespace time
{
	uint32_t getTickCount();
	uint32_t getTickPerMs();
	uint32_t getTickPerUs();

	uint32_t elapsedMicros(unsigned int PreviousTickCounter);

	void msleep(unsigned int nTime);
	void usleep(unsigned int nTime);
}
