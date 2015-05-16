

# This function must be called by each mcu script
function (register_mcu mcu_name)
	#add MCU to list of supported MCUs
	set_property(GLOBAL APPEND PROPERTY __MCU_LIBS ${mcu_name})
endfunction (register_mcu mcu_name)

# show available mcu
function(show_available_mcus)

	get_property(__MCU_LIBS GLOBAL PROPERTY __MCU_LIBS)
	message(STATUS "Available MCUs :")
	foreach(mcu_lib ${__MCU_LIBS})
		message("    [+] ${mcu_lib}")
	endforeach(mcu_lib ${__MCU_LIBS})
endfunction(show_available_mcus)

function (check_is_valid_mcu)
	if (NOT mcu)
		show_available_mcus()
		message (FATAL_ERROR "\n!!!!!!!!!!!!!!!! YOU MUST SPECIFY A BOARD !!!!!!!!!!!!!!!!")
	endif()

	string (TOLOWER ${ARGV0} mcu)

	get_property(__MCU_LIBS GLOBAL PROPERTY __MCU_LIBS)
	list (FIND __MCU_LIBS ${mcu} is_mcu_present)
	if (${is_mcu_present} EQUAL -1)
		show_available_mcus()
		message (FATAL_ERROR "Unknown mcu : ${mcu}\n!!!!!!!!!!!!!!!! YOU MUST SPECIFY A VALID BOARD !!!!!!!!!!!!!!!!")
	endif()
endfunction()


# this include must register each mcu
include(${CMAKE_CURRENT_LIST_DIR}/st/st.mcu)
