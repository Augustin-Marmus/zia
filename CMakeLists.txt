cmake_minimum_required(VERSION 3.9)
project(cpp_zia)

include(Modules/CMakeLists.txt)
include(Core/CMakeLists.txt)
include_directories(sza)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (UNIX)
	set (CMAKE_CXX_FLAGS "-std=c++17")
endif(UNIX)