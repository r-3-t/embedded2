#include <hal/time.h>



namespace
{


	struct AutoInitSysTick
	{

		// Put here the code that need to be run at stratup (before main)
		AutoInitSysTick()
		{


		}
	};

	AutoInitSysTick gAutoInitSysTick;

}

namespace time
{
	uint32_t getTickCount()
	{

	}

	uint32_t getTickPerMs()
	{
	}

	uint32_t getTickPerUs()
	{

	}

	uint32_t elapsedMicros(unsigned int PreviousTickCounter)
	{

	}

	void usleep(unsigned int nTime)
	{

	}

	void msleep(unsigned int nTime)
	{

	}
}
