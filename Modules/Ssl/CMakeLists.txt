cmake_minimum_required(VERSION 3.9)

find_package(OpenSSL REQUIRED)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include ${OPENSSL_INCLUDE_DIR})

if (UNIX)
    add_library(zia-ssl SHARED
            ${CMAKE_CURRENT_LIST_DIR}/include/Ssl.hpp
            ${CMAKE_CURRENT_LIST_DIR}/../Network/include/Socket.hpp

            ${CMAKE_CURRENT_LIST_DIR}/include/SslSocket.hpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/SslSocket.cpp

            ${CMAKE_CURRENT_LIST_DIR}/../Network/srcs/UnixSocket.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Loader.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Ssl.cpp)
endif (UNIX)

if (WIN32)
    add_library(zia-ssl SHARED
            ${CMAKE_CURRENT_LIST_DIR}/include/Ssl.hpp
            ${CMAKE_CURRENT_LIST_DIR}/../Network/include/Socket.hpp

            ${CMAKE_CURRENT_LIST_DIR}/include/SslSocket.hpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/SslSocket.cpp

            ${CMAKE_CURRENT_LIST_DIR}/../Network/srcs/WinSocket.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Loader.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Ssl.cpp)
endif (WIN32)

if (UNIX)
    target_link_libraries(zia-ssl pthread ${OPENSSL_LIBRARIES})
    set (CMAKE_CXX_FLAGS "-std=c++17")
endif(UNIX)


if (WIN32)
    target_link_libraries(zia-ssl Ws2_32 ${OPENSSL_LIBRARIES})
endif(WIN32)