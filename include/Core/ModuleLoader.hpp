//
// Created by marmus_a on 02/02/18.
//

#ifndef CPP_ZIA_MODULELOADER_HPP
#define CPP_ZIA_MODULELOADER_HPP

#ifdef __unix__

#include <Core/UnixModuleLoader.hpp>
using ModuleLoader = UnixModuleLoader;

#endif
#ifdef _WIN32

#include <Netwok/WinSModuleLoader.hpp>
using ModuleLoader = WinModuleLoader;

#endif

#endif //CPP_ZIA_MODULELOADER_HPP
