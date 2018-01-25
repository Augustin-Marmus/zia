cmake_minimum_required(VERSION 3.9)
project(cpp_zia)

set(CMAKE_CXX_STANDARD 17)

include_directories(sza/api)

add_executable(zia
        srcs/main.cpp)
