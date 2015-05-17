cmake_minimum_required(VERSION 2.8)

set(EMBEDDED_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR}/../../)
include(${EMBEDDED_ROOT_PATH}/cmake/project.cmake)

create_project(test_one_wire test_one_wire.cpp)

if (mcus)
	foreach (mcu ${mcus})
		build_project(test_one_wire ${mcu})
	endforeach()
else()
	Log (3, RED "Do not build project : test_one_wire, no mcu selected")
endif()
