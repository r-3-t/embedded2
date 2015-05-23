# Embedded 2
## TOC
* [Supported mcu](#supported-mcu)
* [How to compile an example](#how-to-compile-an-example)
* [Architecture](#architecture)
* [How to add a new mcu](#how-to-add-a-new-mcu)

## Supported mcu
* stm32f407 (stm32f4 discovery)
* [to be supported] stm32f103
* ti ....

## How to compile an example
* arm-none-eabi-gcc must be in PATH
* create a workspace folder (e.g. in embedded2/example/uart/workspace
* type cmake ../ -mcu="stm32f407" (you can specify `-DCMAKE_BUILD_TYPE=<Relesase|Debug>`)
* make
* two files will be created in the workspace folder:
	* ${MCU}_openocd.cfg (e.g. STM32F407_openocd.cfg)
	* ${MCU}_gdbinit (e.g. STM32F407_gdbinit)
* launch openocd -f ${MCU}_openocd.cfg, you should see a message like : 

```
Open On-Chip Debugger 0.7.0 (2015-01-02-12:46)
Licensed under GNU GPL v2
For bug reports, read
	http://openocd.sourceforge.net/doc/doxygen/bugs.html
srst_only separate srst_nogate srst_open_drain connect_deassert_srst
Info : This adapter doesn't support configurable speed
Info : STLINK v2 JTAG v17 API v2 SWIM v0 VID 0x0483 PID 0x3748
Info : Target voltage: 2.885076
Info : stm32f4x.cpu: hardware has 6 breakpoints, 4 watchpoints
```

* lauchn `arm-none-eabi-gdb test_uart_stm32f407 --ix STM32F407_gdbinit`:
	* type `monitor reset init`
	* type `load`
	* type `c` (continue)

## Architecture 

```
embedded2
	|
	|____ backend	: specific code of each mcu 
	|
	|____ cmake		: cmake scripts
	|
	|____ driver	: driver only needs hal to be implemented. They work on all mcus  
	|
	|____ example	: code examples
	|
	|____ hal		: hardware abstraction layer.
					  example must only use these headers
```
## How to add a new mcu
Look at the template folder in backend. You must fill some files :

* a cmake file which describes the mcu
* cpp files in the impl folder (uart, gpio, ...)
* mcu_internal.h which is include in all hal files. It allows to store private variables member.
