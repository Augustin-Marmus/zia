cmake_minimum_required(VERSION 3.9)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

if (UNIX)
    add_library(zia-logger SHARED
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Logger.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Loader.cpp

            ${CMAKE_CURRENT_LIST_DIR}/include/Logger.hpp)
endif (UNIX)

if (WIN32)
    add_library(zia-logger SHARED
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Logger.cpp)
endif (WIN32)


if (UNIX)

    set (CMAKE_CXX_FLAGS "-std=c++17")

    add_executable(testLogger
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Logger.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Loader.cpp

            ${CMAKE_CURRENT_LIST_DIR}/include/Logger.hpp
            ${CMAKE_CURRENT_LIST_DIR}/tests/LoggerTest.cpp)
    target_link_libraries(testLogger ${Boost_LIBRARIES})
    add_test(TestBoost testLogger)
endif(UNIX)


if (WIN32)
    target_link_libraries(zia-logger)
endif(WIN32)
