//
// Created by marmus_a on 29/01/18.
//

#include <iostream>
#include "Core/UnixModuleLoader.hpp"


UnixModuleLoader::UnixModuleLoader() {
    this->handler = nullptr;
}

UnixModuleLoader::~UnixModuleLoader() {
    if (this->handler) {
        dlclose(this->handler);
    }
}

bool UnixModuleLoader::loadLibrary(const std::string& path, const std::string &file) {
    std::cout << "Loading: " << "lib" + file + ".so" << std::endl;
    if (this->handler) {
        unloadModule();
    }
    return (!!(this->handler = dlopen((path + "lib" + file + ".so").c_str(), RTLD_LAZY)));
}

zia::api::Module* UnixModuleLoader::loadModule(const std::string &moduleName) {
    zia::api::Module*   (*ptr)();

    ptr = reinterpret_cast<zia::api::Module*(*)()>(dlsym(this->handler, (std::string("get") + moduleName).c_str()));
    if (ptr) {
        return (ptr());
    } else {
        return (nullptr);
    }
}

bool UnixModuleLoader::unloadModule() {
    dlclose(this->handler);
    this->handler = nullptr;
}

zia::api::Net* UnixModuleLoader::loadNetwork() {
    zia::api::Net*   (*ptr)();

    ptr = reinterpret_cast<zia::api::Net*(*)()>(dlsym(this->handler, "getNetwork"));
    if (ptr) {
        return (ptr());
    } else {
        return (nullptr);
    }
}