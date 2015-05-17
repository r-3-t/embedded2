# do not forget to add this file to embedded2/backend/mcus.cmake (at the end of the file)


# register the new mcu:
Log(9, YELLOW "adding my_new_mcu mcu")
register_mcu("my_new_mcu")



# create a library object : the library must have the name  MY_NEW_MCU_LIB

add_library(MY_NEW_MCU_LIB 	OBJECT 	${ALL_MCU_NEEDED_FILES}
									${STM32F407_ROOT_DIR}/impl/gpio.cpp
									${STM32F407_ROOT_DIR}/impl/uart.cpp
									${STM32F407_ROOT_DIR}/impl/time.cpp
						)                     

# you can add compile definitions, compile options and include directories
target_compile_definitions(MY_NEW_MCU_LIB PUBLIC ${MY_NEW_MCU_COMPILE_DEFINITIONS}) # e.g. -DHSE_VALUE=8000000
target_compile_options(MY_NEW_MCU_LIB PUBLIC ${MY_NEW_MCU_COMPILE_FLAGS}) 			# e.g. -mthumb -mcpu=cortex-m4
target_include_directories(MY_NEW_MCU_LIB 		PRIVATE 	
													${EMBEDDED_ROOT_DIR}
													${EMBEDDED_ROOT_DIR}/backend/

												PUBLIC
													<PATH TO mcu_internal.h>
												)