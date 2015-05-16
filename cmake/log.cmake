# The MIT License (MIT)

# Copyright (c) 2015 jp luyten

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.


# This functions add log capabilities to cmake

if (LOG_FUNCTIONS_FOUND)
	return()
endif()

message (STATUS "include log.cmake")

if (NOT GLOBAL_VAR_LOG_FUNCTION_)
	set (LOG_LEVEL						9 CACHE INTERNAL "log level")
	set (LOG_FILE							0 CACHE INTERNAL "log file")
	set(indentation_value			0 CACHE INTERNAL "indentation level")
	set (GLOBAL_VAR_LOG_FUNCTION_   on CACHE INTERNAL "global var for log function loaded")
endif()

# helper to get a relative path from the top level source dir
function(get_relative_path RELATIVE_PATH ABSOLUTE_PATH)
	file(RELATIVE_PATH relative ${CMAKE_SOURCE_DIR} ${ABSOLUTE_PATH})
	set(${RELATIVE_PATH} ${relative} PARENT_SCOPE)
endfunction()

# update log_level.
# if a call is made to the log function and if level is less than log_level, then log message is ignored
function (set_log_level level)
	set (LOG_LEVEL	${level} CACHE INTERNAL "log level")
endfunction()

# increment indententation level
function (Log_enter)
	math (EXPR my_indentation_value "${indentation_value} + 1")
	set (indentation_value ${my_indentation_value} CACHE INTERNAL "indentation level")
endfunction()

# decrement indendtention level
function (Log_leave)
	math (EXPR my_indentation_value "${indentation_value} - 1")
	set (indentation_value ${my_indentation_value} CACHE INTERNAL "indentation level")
endfunction()

# set the log_file to filename
# this function can be only called once
# other calls are ignored
function (set_log_file	filename)
	if (EXISTS ${LOG_FILE} OR LOG_FILE STREQUAL "STDOUT")
		Log(9 "ignoring call to set log file with param : ${filename}")
		return()
	endif()
	if (filename STREQUAL "STDOUT")
		set (LOG_FILE "STDOUT" CACHE INTERNAL "log file")
	else()
		set (LOG_FILE "${CMAKE_BINARY_DIR}/${filename}" CACHE INTERNAL "log file")
	endif()

	if (WIN32)
		execute_process (	COMMAND				cmd /C date /T
							OUTPUT_VARIABLE		CURRENT_DATE)
		execute_process (	COMMAND				cmd /C time /T
							OUTPUT_VARIABLE		CURRENT_TIME)
	elseif (APPLE)
		execute_process (	COMMAND				date "+%d/%m/%Y"
							OUTPUT_VARIABLE		CURRENT_DATE)
		execute_process (	COMMAND				date "+%H:%M"
							OUTPUT_VARIABLE		CURRENT_TIME)
	elseif (UNIX)
		execute_process (	COMMAND				date "+%d/%m/%Y"
							OUTPUT_VARIABLE		CURRENT_DATE)
		execute_process (	COMMAND				date "+%H:%M"
							OUTPUT_VARIABLE		CURRENT_TIME)
	else()
		message (FATAL_ERROR  "don't know how to get the current time / date on this system")
	endif()
	
	string (REPLACE "\n" "" CURRENT_DATE ${CURRENT_DATE})
	string (REPLACE "\n" "" CURRENT_TIME ${CURRENT_TIME})

	set (log_header  "--------- BUILD start at : ${CURRENT_DATE} - ${CURRENT_TIME} ---------\n")
	if (${LOG_FILE} STREQUAL "STDOUT")
		message (${log_header})
	else()
		file (WRITE	${LOG_FILE} ${log_header})
	endif()
endfunction()

# Log function
# first arg is the log level
# others args are the log message
# Log supports color:
# Log (1, RED "This is a red message")
function (Log level)
	if (${level} GREATER ${LOG_LEVEL})
		return ()
	endif()
	list (REMOVE_AT ARGV 0)

	get_relative_path(CURRENT_FILE ${CMAKE_CURRENT_LIST_FILE})

	set(INDENT "")
	if (indentation_value GREATER 0)
		math (EXPR my_indentation_value "${indentation_value} - 1")
		foreach(loop_var RANGE ${my_indentation_value})
			set(INDENT "    ${INDENT}")
		endforeach()
	endif()

  colorized_str(log_msg ${ARGV})

	set (log_message "${CURRENT_FILE}: ${INDENT}${log_msg}")

	if (EXISTS ${LOG_FILE})
		file (APPEND ${LOG_FILE}	"${log_message}\n")
	else()
		message (${log_message})
	endif()

endfunction()

function (colorized_str output)
	string (ASCII 27 _escape)
	set(WHITE "29")
	set(GRAY "30")
	set(RED "31")
	set(GREEN "32")
	set(YELLOW "33")
	set(BLUE "34")
	set(MAG "35")
	set(CYAN "36")

	set (output_name ${ARGV0})
	list (REMOVE_AT ARGV 0)

	foreach (color WHITE GRAY RED GREEN YELLOW BLUE MAG CYAN)
		set(HI${color} "1\;${${color}}")
		set(LO${color} "2\;${${color}}")
		set(_${color}_ "4\;${${color}}")
		set(_HI${color}_ "1\;4\;${${color}}")
		set(_LO${color}_ "2\;4\;${${color}}")
	endforeach()

	set(str "")
	set(coloron FALSE)
	foreach(arg ${ARGV})
		if (NOT "${${arg}}" STREQUAL "")
			#if (CMAKE_COLOR_MAKEFILE)
				set(str "${str}${_escape}[${${arg}}m")
				set(coloron TRUE)
			#endif()
		else()
			set(str "${str}${arg}")
			if (coloron)
				set(str "${str}${_escape}[0m")
				set(coloron FALSE)
			endif()
			set(str "${str} ")
		endif()
	endforeach()
	set (${output_name} ${str} PARENT_SCOPE)
endfunction()

function (colormsg)
	colorized_str (str ${ARGV})
	message(${str})
endfunction()

set (LOG_FUNCTIONS_FOUND on)
