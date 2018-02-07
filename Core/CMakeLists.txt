cmake_minimum_required(VERSION 3.9)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

if (UNIX)
    add_executable(zia
            # CLion Project Includes
            ${CMAKE_CURRENT_LIST_DIR}/include/Pipeline.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/ModuleLoader.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/ThreadPool.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/IModuleLoader.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/UnixModuleLoader.hpp

            sza/api/http.h
            sza/api/net.h
            sza/api/conf.h
            sza/api/module.h

            ${CMAKE_CURRENT_LIST_DIR}/srcs/Pipeline.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/main.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/UnixModuleLoader.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/ThreadPool.cpp)
endif (UNIX)

if (WIN32)
    add_executable(zia
            # CLion Project Includes
            ${CMAKE_CURRENT_LIST_DIR}/include/Pipeline.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/ModuleLoader.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/ThreadPool.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/IModuleLoader.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/WinModuleLoader.hpp

            sza/api/http.h
            sza/api/net.h
            sza/api/conf.h
            sza/api/module.h

            ${CMAKE_CURRENT_LIST_DIR}/srcs/Pipeline.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/main.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/WinModuleLoader.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/ThreadPool.cpp)
endif (WIN32)

add_executable(testCompilationBoost ${CMAKE_CURRENT_LIST_DIR}/tests/testBoostCompilation.cpp)
target_link_libraries(testCompilationBoost ${Boost_LIBRARIES})
add_test(TestBoost testCompilationBoost)

if (UNIX)
    target_link_libraries(zia dl pthread)
endif(UNIX)

if (WIN32)
    target_link_libraries(zia Kernel32)
endif(WIN32)