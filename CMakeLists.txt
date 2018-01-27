cmake_minimum_required(VERSION 3.9)
project(cpp_zia)

set(CMAKE_CXX_STANDARD 17)

set (CMAKE_CXX_FLAGS "-std=c++17")

include_directories(sza include)

add_executable(zia
        # CLion Project Includes
        include/Network/ISocket.hpp
        include/Network/UnixSocket.hpp
		include/Core/Pipeline.hpp

        sza/api/http.h
        sza/api/net.h
        sza/api/conf.h
        sza/api/module.h

        srcs/Network/UnixSocket.cpp
		srcs/Core/Pipeline.cpp
        srcs/main.cpp  )
