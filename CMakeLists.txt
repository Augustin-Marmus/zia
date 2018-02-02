cmake_minimum_required(VERSION 3.9)
project(cpp_zia)

include_directories(sza include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (UNIX)
add_executable(zia
        # CLion Project Includes
		include/Core/Pipeline.hpp
		include/Core/ModuleLoader.hpp
		include/Core/ThreadPool.hpp

        sza/api/http.h
        sza/api/net.h
        sza/api/conf.h
        sza/api/module.h

		srcs/Core/Pipeline.cpp
        srcs/main.cpp
		srcs/Core/UnixModuleLoader.cpp
		srcs/Core/ThreadPool.cpp)
endif (UNIX)

if (WINDOW)
	add_executable(zia
			# CLion Project Includes
			include/Core/Pipeline.hpp
			include/Core/ModuleLoader.hpp
			include/Core/ThreadPool.hpp

			sza/api/http.h
			sza/api/net.h
			sza/api/conf.h
			sza/api/module.h

			srcs/Core/Pipeline.cpp
			srcs/main.cpp
			srcs/Core/WinModuleLoader.cpp
			srcs/Core/ThreadPool.cpp)
endif (WINDOW)

if (UNIX)
	add_library(zia-network SHARED
			include/Network/Socket.hpp
			include/Network/Network.hpp

			srcs/Network/UnixSocket.cpp
			srcs/Network/Loader.cpp
			srcs/Network/Network.cpp)
endif (UNIX)

if (WINDOW)
	add_library(zia-network SHARED
			include/Network/Socket.hpp
			include/Network/Network.hpp

			srcs/Network/Loader.cpp
			srcs/Network/Network.cpp)
endif (WINDOW)

if (UNIX)
	target_link_libraries(zia dl pthread)
	target_link_libraries(zia-network pthread)
	set (CMAKE_CXX_FLAGS "-std=c++17 -ggdb3")
endif(UNIX)