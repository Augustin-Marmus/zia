cmake_minimum_required(VERSION 3.9)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

if (UNIX)
    add_library(zia-ssl SHARED
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Ssl.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Loader.cpp

            ${CMAKE_CURRENT_LIST_DIR}/include/Ssl.hpp)
endif (UNIX)

if (WIN32)
    add_library(zia-ssl SHARED
            ${CMAKE_CURRENT_LIST_DIR}/srcs/WinSocket.cpp)
endif (WIN32)


if (UNIX)
    enable_testing()
    target_link_libraries(zia-ssl pthread)

    set (CMAKE_CXX_FLAGS "-std=c++17")

    add_executable(testCompilationBoostSsl
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Ssl.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Loader.cpp

            ${CMAKE_CURRENT_LIST_DIR}/include/Ssl.hpp
            ${CMAKE_CURRENT_LIST_DIR}/tests/tests_ssl.cpp)
    target_link_libraries(testCompilationBoostSsl ${Boost_LIBRARIES})
    add_test(TestBoost testCompilationBoostSsl)

endif(UNIX)


if (WIN32)
    target_link_libraries(zia-ssl Ws2_32)
endif(WIN32)