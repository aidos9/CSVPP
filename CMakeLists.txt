option(ENABLE_TESTS "Compile tests" ON)

cmake_minimum_required(VERSION 3.12)

project(CSV LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CSV_SOURCES src/csvDocument.cpp
	src/csvException.cpp
	src/csvStringDocument.cpp
  src/csvRow.cpp
  src/csvStreamDocument.cpp)

set(CSV_HEADERS include/csvDocument.h
	include/csvRow.h
	include/csvException.h
  include/csvStringDocument.h
	include/csvStreamDocument.h
	include/csv.h)

include(CheckIncludeFileCXX)
include(CheckIncludeFile)

CHECK_INCLUDE_FILE_CXX(iostream HAS_IOSTREAM)
CHECK_INCLUDE_FILE_CXX(vector HAS_VECTOR)
CHECK_INCLUDE_FILE_CXX(istream HAS_ISTREAM)
CHECK_INCLUDE_FILE_CXX(algorithm HAS_ALGORITHM)
CHECK_INCLUDE_FILE_CXX(string HAS_STRING)
CHECK_INCLUDE_FILE_CXX(map HAS_MAP)
CHECK_INCLUDE_FILE_CXX(sstream HAS_SSTREAM)
CHECK_INCLUDE_FILE_CXX(stdexcept HAS_STDEXCEPT)

if(NOT HAS_VECTOR)
    message(FATAL_ERROR "Could not find #include <vector>")
endif(NOT HAS_VECTOR)

if(NOT HAS_ISTREAM)
    message(FATAL_ERROR "Could not find #include <istream>")
endif(NOT HAS_ISTREAM)

if(NOT HAS_ALGORITHM)
    message(FATAL_ERROR "Could not find #include <algorithm>")
endif(NOT HAS_ALGORITHM)

if(NOT HAS_STRING)
    message(FATAL_ERROR "Could not find #include <string>")
endif(NOT HAS_STRING)

if(NOT HAS_MAP)
    message(FATAL_ERROR "Could not find #include <map>")
endif(NOT HAS_MAP)

if(NOT HAS_SSTREAM)
    message(FATAL_ERROR "Could not find #include <sstream>")
endif(NOT HAS_SSTREAM)

if(NOT HAS_STDEXCEPT)
    message(FATAL_ERROR "Could not find #include <stdexcept>")
endif(NOT HAS_STDEXCEPT)

add_library(${PROJECT_NAME} STATIC ${CSV_SOURCES} ${CSV_HEADERS})
add_library(${PROJECT_NAME}Shared SHARED ${CSV_SOURCES} ${CSV_HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${CSV_HEADERS}")
set_target_properties(${PROJECT_NAME}Shared PROPERTIES PUBLIC_HEADER "${CSV_HEADERS}")

if(ENABLE_TESTS)
		if(NOT HAS_IOSTREAM)
	  	message(FATAL_ERROR "Could not find #include <iostream>")
		endif(NOT HAS_IOSTREAM)

    include(CTest)
    add_subdirectory(tests)
endif(ENABLE_TESTS)
