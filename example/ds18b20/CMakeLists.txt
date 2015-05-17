cmake_minimum_required(VERSION 2.8)

set(EMBEDDED_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR}/../../)
include(${EMBEDDED_ROOT_PATH}/cmake/project.cmake)

create_project(test_ds18b20 test_ds18b20.cpp)

if (mcus)
	foreach (mcu ${mcus})
		build_project(test_ds18b20 ${mcu})
	endforeach()
else()
	Log (3, RED "Do not build project : test_ds18b20, no mcu selected")
endif()
