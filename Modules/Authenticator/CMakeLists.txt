cmake_minimum_required(VERSION 3.9)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

if (UNIX)
    add_library(zia-auth SHARED
            ${CMAKE_CURRENT_LIST_DIR}/include/Authenticator.hpp
            
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Loader.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Authenticator.cpp)

    set (CMAKE_CXX_FLAGS "-std=c++17")

    add_executable(testAuth
            ${CMAKE_CURRENT_LIST_DIR}/include/Authenticator.hpp

            ${CMAKE_CURRENT_LIST_DIR}/srcs/Loader.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Authenticator.cpp
            ${CMAKE_CURRENT_LIST_DIR}/tests/testsAuth.cpp)
    target_link_libraries(testAuth ${Boost_LIBRARIES})
    add_test(TestBoost testAuth)
endif(UNIX)