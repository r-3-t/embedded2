cmake_minimum_required(VERSION 2.8)

set(EMBEDDED_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR}/../../../)
include(${EMBEDDED_ROOT_PATH}/cmake/project.cmake)

create_project(uart_proxy uart_proxy.cpp)

if (mcus)
	foreach (mcu ${mcus})
		build_project(uart_proxy ${mcu})
	endforeach()
else()
	Log (3, RED "Do not build project : test_uart, no mcu selected")
endif()
