cmake_minimum_required(VERSION 3.9)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

if (UNIX)
    add_library(zia-html SHARED
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Html.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Loader.cpp

          ${CMAKE_CURRENT_LIST_DIR}/include/Html.hpp)
endif (UNIX)

if (WIN32)
    add_library(zia-html SHARED
            ${CMAKE_CURRENT_LIST_DIR}/srcs/WinSocket.cpp)
endif (WIN32)


if (UNIX)
    enable_testing()
    target_link_libraries(zia-html pthread)

    set (CMAKE_CXX_FLAGS "-std=c++17")

    add_executable(testHtml
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Html.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Loader.cpp

            ${CMAKE_CURRENT_LIST_DIR}/include/Html.hpp
          ${CMAKE_CURRENT_LIST_DIR}/tests/HtmlTests.cpp)
    target_link_libraries(testHtml ${Boost_LIBRARIES})
    add_test(TestBoost testHtml)
endif(UNIX)


if (WIN32)
    target_link_libraries(zia-html Ws2_32)
endif(WIN32)
