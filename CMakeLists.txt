cmake_minimum_required(VERSION 3.9)
project(cpp_zia)

set(CMAKE_CXX_STANDARD 17)

include_directories(sza/api include)

add_executable(zia
        srcs/Network/UnixSocket.cpp
        srcs/main.cpp)
