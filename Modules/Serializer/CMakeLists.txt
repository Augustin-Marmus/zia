cmake_minimum_required(VERSION 3.9)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

if (UNIX)
    add_library(zia-serializer SHARED
            ${CMAKE_CURRENT_LIST_DIR}/include/Serializer.hpp

            ${CMAKE_CURRENT_LIST_DIR}/srcs/Loader.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Serializer.cpp)
endif (UNIX)

if (WIN32)
    add_library(zia-serializer SHARED
            ${CMAKE_CURRENT_LIST_DIR}/include/Socket.hpp

            ${CMAKE_CURRENT_LIST_DIR}/srcs/Loader.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Serializer.cpp)
endif (WIN32)

if (UNIX)
    target_link_libraries(zia-serializer)
    set (CMAKE_CXX_FLAGS "-std=c++17")
endif(UNIX)


if (WIN32)
    target_link_libraries(zia-serializer)
endif(WIN32)