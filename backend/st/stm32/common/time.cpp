#include <hal/time.h>

#if defined STM32F407
#	include "stm32f4xx.h"
#elif defined STM32F103
#	include "stm32f10x.h"
#else
#	error "Unknown mcu"
#endif

namespace
{

	uint32_t guTickFactor;
	uint32_t gmTickFactor;

	struct AutoInitSysTick
	{
		AutoInitSysTick()
		{
			//update SystemCoreClock to the right frequency
			SystemCoreClockUpdate();

			//set ms and us factor
		    guTickFactor = SystemCoreClock / 1000000;
		    gmTickFactor = SystemCoreClock / 1000;

		    //enable systick
		    SysTick->LOAD = 0x00ffffff;
		    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk; //processor clock

		}
	};

	AutoInitSysTick gAutoInitSysTick;

}

namespace time
{
	uint32_t getTickCount()
	{
		return SysTick->VAL;
	}

	void decrease_ticks(uint32_t nbTicks)
	{
		uint16_t PreviousTickCounter = getTickCount();
		uint16_t CurrentTickCounter;

		//ticks count in one iteration
		uint16_t elapseTicks = 0;

		while( nbTicks > elapseTicks)
		{
			//decrease total ticks counter
			nbTicks -= elapseTicks;

			//calculate ticks count between now and previous iteration
			CurrentTickCounter = getTickCount();
			elapseTicks = PreviousTickCounter - CurrentTickCounter;
			PreviousTickCounter = CurrentTickCounter;

		}
	}

	uint32_t elapsedMicros(unsigned int PreviousTickCounter)
	{
		uint32_t CurrentTickCounter = getTickCount();
		uint32_t elapseTicks;

		if (CurrentTickCounter > PreviousTickCounter)
		{
			elapseTicks = 0xFFFFFF - (CurrentTickCounter - PreviousTickCounter);
		}
		else
		{
			elapseTicks = PreviousTickCounter - CurrentTickCounter;
		}

		return (elapseTicks/guTickFactor);
	}

	void usleep(unsigned int nTime)
	{
		//ticks count for the requested time
		decrease_ticks(nTime * guTickFactor);
	}

	void msleep(unsigned int nTime)
	{
		//ticks count for the requested time
		decrease_ticks(nTime * gmTickFactor);
	}

	uint32_t getTickPerMs()
	{
		return gmTickFactor;
	}

	uint32_t getTickPerUs()
	{
		return guTickFactor;
	}
}
