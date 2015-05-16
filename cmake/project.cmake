set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/)
set (EMBEDDED_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../)

include (log)

# configure compiler
include(arm-none-eabi-gcc)

# #common compile flags
# if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
# 	set(COMMON_COMPILE_FLAGS "-O0 -g -Werror -Wno-error=cpp -Wextra -Warray-bounds -ffunction-sections -fdata-sections")
# else()
# 	set(COMMON_COMPILE_FLAGS "-O3 -Werror -Wno-error=cpp -Wextra -Warray-bounds -ffunction-sections -fdata-sections -fno-toplevel-reorder")
# 	add_definitions(-DNDEBUG)
# endif()
# #set(COMMON_COMPILE_FLAGS "-Os -Werror -Wextra -Warray-bounds -ffunction-sections -fdata-sections")
# #-u _printf_float
# set(COMMON_LINK_FLAGS "-Wl,--gc-sections --specs=nano.specs -u _printf_float")


# find mcu
include (${CMAKE_MODULE_PATH}/../backend/mcus.cmake)

#-------------------------------------------------------------------------------

# create a linker script fot the specified mcu
function (create_linker_script_for_mcu)

	check_is_valid_mcu (${ARGV0})
	string (TOUPPER ${ARGV0} MCU)

	#build linker script
	set (_FLASH_ORIGIN		${${MCU}_FLASH_ORIGIN})
	set (_RAM_ORIGIN		${${MCU}_RAM_ORIGIN})
	set (_RAM_SIZE			${${MCU}_RAM_SIZE})
	set (_FLASH_SIZE		${${MCU}_FLASH_SIZE})
	set (_MIN_STACK_SIZE	${${MCU}_MIN_STACK_SIZE})
	set (_MIN_HEAP_SIZE		${${MCU}_MIN_HEAP_SIZE})

	configure_file(${EMBEDDED_ROOT_DIR}/backend/linker_script.ld ${CMAKE_CURRENT_BINARY_DIR}/linker_script_${MCU}.ld )
	set (LDSCRIPT "${CMAKE_CURRENT_BINARY_DIR}/linker_script_${MCU}.ld" PARENT_SCOPE)
endfunction(create_linker_script_for_mcu)

#-------------------------------------------------------------------------------

function (create_debug_files mcu)
	string (TOUPPER ${mcu} MCU)
	#GDB / OpenOCD
	set (GDBINIT_CONTENT
	"
	target remote localhost:3333
	monitor reset init
	")

	file (WRITE ${CMAKE_CURRENT_BINARY_DIR}/.gdbinit ${GDBINIT_CONTENT})
	file (WRITE ${CMAKE_CURRENT_BINARY_DIR}/openocd.cfg ${${MCU}_OPENOCDCFG_CONTENT})
endfunction()

#-------------------------------------------------------------------------------

# this function create a project
# to build a project, you must associate it with a mcu
# thanks to the function build_project
function (create_project project_name)
	list(REMOVE_AT ARGV 0)
	set(sources ${ARGV})
	set_property(GLOBAL PROPERTY __PROJECT_${project_name} ${sources})
	log (2, BLUE "Create project '${project_name}'")
endfunction()

# build a project :
#					project_name : a proeviously created project (see create_project)
#					mcu : the target board
# the same project can be created with several mcu
function (build_project project_name mcu)
	set (target_project_name ${project_name}_${mcu})

	log (2, BLUE "instanciate project '${project_name}' for mcu : ${mcu}, project name : ${target_project_name}")

	string (TOUPPER ${mcu} MCU)

	get_property(project_sources GLOBAL PROPERTY __PROJECT_${project_name})
	add_executable(${target_project_name} $<TARGET_OBJECTS:${MCU}_LIB> ${project_sources} ${EMBEDDED_ROOT_DIR}/backend/syscall.c)
	target_compile_definitions(${target_project_name} PRIVATE $<TARGET_PROPERTY:${MCU}_LIB,COMPILE_DEFINITIONS>)
	target_compile_options(${target_project_name}  PRIVATE $<TARGET_PROPERTY:${MCU}_LIB,COMPILE_OPTIONS>) 

	create_linker_script_for_mcu(${mcu})
	target_include_directories(${target_project_name} PRIVATE ${EMBEDDED_ROOT_DIR}
															   $<TARGET_PROPERTY:${MCU}_LIB,INCLUDE_DIRECTORIES>)
	target_link_libraries(${target_project_name}  ${${MCU}_LINK_FLAGS} -T ${LDSCRIPT})
	set_target_properties(${target_project_name} PROPERTIES LINK_FLAGS ${EMBEDDED_LINK_FLAGS})

	add_custom_command (TARGET ${target_project_name} POST_BUILD COMMAND arm-none-eabi-size $<TARGET_FILE:${target_project_name}>)
	add_custom_command (TARGET ${target_project_name} POST_BUILD COMMAND arm-none-eabi-objcopy $<TARGET_FILE:${target_project_name}> -O binary $<TARGET_FILE_DIR:${target_project_name}>/$<TARGET_FILE_NAME:${target_project_name}>.bin)
	#add_custom_command (TARGET ${target_project_name} POST_BUILD COMMAND arm-none-eabi-strip $<TARGET_FILE:${target_project_name}>)

	create_debug_files(${mcu})
endfunction()

#-------------------------------------------------------------------------------

# function (add_mcu_lib mcu_lib_name)
# 	list(REMOVE_AT ARGV 0)
# 	set(sources ${ARGV})

# 	#add all sources for this MCU
# 	foreach (source ${sources})
# 		if (IS_DIRECTORY ${source})
# 			file(GLOB directory_source_files ${source}/*)
# 			LIST(APPEND source_files ${directory_source_files})
# 			LIST(APPEND directories_to_include ${source})
# 		else(IS_DIRECTORY ${source})
# 			LIST(APPEND source_files ${source})
# 		endif(IS_DIRECTORY ${source})
# 	endforeach(source)

# 	#add MCU target
# 	add_library(${mcu_lib_name} OBJECT ${source_files})

# 	#add previously found directories to includes
# 	target_include_directories(${mcu_lib_name} PUBLIC ${directories_to_include})

# 	string(TOUPPER ${mcu_lib_name} MCU_LIB_NAME)

# 	#add needed flags for this MCU
# 	set_target_properties(${mcu_lib_name} PROPERTIES COMPILE_FLAGS ${${MCU_LIB_NAME}_COMPILE_FLAGS})

# endfunction(add_mcu_lib)

# function (add_mcu_hal mcu_hal_name mcu_lib_name source_path header_path)
# 	file(GLOB source_files ${source_path}/*.cpp)
# 	file(GLOB header_files ${header_path}/*.h*)

# 	message ("Create mcu hal : ${mcu_hal_name} with : ${source_files} ${header_files}")
# 	add_library(${mcu_hal_name} OBJECT ${source_files} ${header_files})

# 	target_include_directories(${mcu_hal_name} PUBLIC ${header_path})

# 	string(TOUPPER ${mcu_lib_name} MCU_LIB_NAME)

# 	# do not append header automaticaly
# 	#foreach(header ${header_files})
# 	#	LIST(APPEND include_headers -include${header})
# 	#endforeach(header)
# 	#target_compile_options(${mcu_hal_name} PUBLIC ${include_headers})

# 	set_target_properties(${mcu_hal_name} PROPERTIES COMPILE_FLAGS ${${MCU_LIB_NAME}_COMPILE_FLAGS})

# 	#target_link_libraries(${mcu_hal_name} pinout)

# 	#target_link_libraries(${mcu_hal_name} ${mcu_lib_name})

# endfunction(add_mcu_hal)




# function (build_project project_name)
# 	if (NOT mcu)
# 		show_available_mcus()
# 		message(FATAL_ERROR "No MCU selected ! Use -Dmcu=")
# 		return()
# 	endif(NOT mcu)

# 	get_property(MCU_LIBS GLOBAL PROPERTY MCU_LIBS)
# 	list (FIND MCU_LIBS ${mcu} IsMcuExists)
# 	if (IsMcuExists EQUAL -1)		
# 		message(FATAL_ERROR "Invalid MCU selected !!! Please selct one in : ${MCU_LIBS}")
# 		return()
# 	endif(IsMcuExists EQUAL -1)


# 	if (NOT EXISTS ${project_${mcu}})
# 		message (FATAL_ERROR "'backend '${mcu}' does not provide a project_${mcu} variable that contains the file to create ${mcu} library' ('${project_${mcu}}')")
# 	endif()

# 	# call the mcu cmake file
# 	include(${project_${mcu}})

# 	list(REMOVE_AT ARGV 0)
# 	set(source_files ${ARGV})

# 	add_executable(${project_name} ${source_files} $<TARGET_OBJECTS:syscall> $<TARGET_OBJECTS:error> $<TARGET_OBJECTS:hal_${mcu}> $<TARGET_OBJECTS:${mcu}> $<TARGET_OBJECTS:pinout>)
# 	target_link_libraries(${project_name}  ${${MCU}_LINK_FLAGS} -T${LDSCRIPT})

# 	include_directories($<TARGET_PROPERTY:pinout,INCLUDE_DIRECTORIES>)
# 	include_directories($<TARGET_PROPERTY:${mcu},INCLUDE_DIRECTORIES>)
# 	#include_directories($<TARGET_PROPERTY:hal_${mcu},INCLUDE_DIRECTORIES>)

# 	target_compile_options(${project_name} PUBLIC $<TARGET_PROPERTY:hal_${mcu},COMPILE_OPTIONS>)
# 	target_compile_definitions(${project_name} PUBLIC $<TARGET_PROPERTY:hal_${mcu},COMPILE_DEFINITIONS>)

# 	#TODO: process automaticaly	
# 	set_target_properties(${project_name} pinout syscall error PROPERTIES COMPILE_FLAGS ${${MCU}_COMPILE_FLAGS})

# 	#Templates
# 	math(EXPR NUM_LED "${${MCU}_NUM_LED} - 1")
# 	message (STATUS "NUM_LED : ${NUM_LED}")
# 	foreach (led_number RANGE ${NUM_LED})
# 		message (STATUS "Add led ${led_number}")
# 		list(APPEND MCU_TEMPLATE LED${led_number}_PORT=${${MCU}_LED${led_number}_PORT};LED${led_number}_PIN=${${MCU}_LED${led_number}_PIN};)
# 	endforeach()
# 	list(APPEND MCU_TEMPLATE BUTTON0_PORT=${${MCU}_BUTTON0_PORT};BUTTON0_PIN=${${MCU}_BUTTON0_PIN})
# 	list(APPEND MCU_TEMPLATE DEFAULT_UART=${${MCU}_DEFAULT_UART};DEFAULT_TIMER=${${MCU}_DEFAULT_TIMER})

# 	target_compile_definitions(${project_name} PUBLIC ${MCU_TEMPLATE})

# 	add_custom_command (TARGET ${project_name} POST_BUILD COMMAND arm-none-eabi-size $<TARGET_FILE:${project_name}>)
# 	add_custom_command (TARGET ${project_name} POST_BUILD COMMAND arm-none-eabi-objcopy $<TARGET_FILE:${project_name}> -O binary $<TARGET_FILE_DIR:${project_name}>/$<TARGET_FILE_NAME:${project_name}>.bin)
# 	add_custom_command (TARGET ${project_name} POST_BUILD COMMAND arm-none-eabi-strip $<TARGET_FILE:${project_name}>)

# endfunction(build_project)

# function (build_library library_name)
# 	if (NOT mcu)
# 		show_available_mcus()
# 		message(FATAL_ERROR "No MCU selected ! Use -Dmcu=")
# 		return()
# 	endif(NOT mcu)

# 	list(REMOVE_AT ARGV 0)
# 	set(source_files ${ARGV})

# 	add_library(${library_name} OBJECT ${source_files})

# 	#TODO: process automaticaly	
# 	set_target_properties(${library_name} PROPERTIES COMPILE_FLAGS ${${MCU}_COMPILE_FLAGS})

# 	#Templates
# 	math(EXPR NUM_LED "${${MCU}_NUM_LED} - 1")
# 	message (STATUS "NUM_LED : ${${MCU}_NUM_LED}")
# 	foreach (led_number RANGE ${NUM_LED})
# 		message (STATUS "Add led ${led_number}")
# 		list(APPEND MCU_TEMPLATE LED${led_number}_PORT=${${MCU}_LED${led_number}_PORT};LED${led_number}_PIN=${${MCU}_LED${led_number}_PIN};)
# 	endforeach()
# 	list(APPEND MCU_TEMPLATE BUTTON0_PORT=${${MCU}_BUTTON0_PORT};BUTTON0_PIN=${${MCU}_BUTTON0_PIN})
# 	list(APPEND MCU_TEMPLATE DEFAULT_UART=${${MCU}_DEFAULT_UART};DEFAULT_TIMER=${${MCU}_DEFAULT_TIMER})

# 	target_compile_definitions(${library_name} PUBLIC ${MCU_TEMPLATE})

# endfunction(build_library)

#add optional arduino frontend
#include(${CMAKE_CURRENT_LIST_DIR}/../../frontends/arduino/arduino.cmake)
