//
// Created by marmus_a on 09/02/18.
//

#include "Core.hpp"

Core::Core() {
    std::cout << "Constructing Core" << std::endl;
}


Core::~Core() {
    std::cout << "Destructing Core" << std::endl;
    if (this->net) {
        this->net.reset();
    }
}

bool Core::run(const zia::api::Conf& config) {
    if (!this->config(config)) {
        std::cerr << "Failed to configure Core" << std::endl;
        return (false);
    }
    this->net->run(this->pipeline.getCallback());
}

bool Core::config(const zia::api::Conf& config) {
    this->moduleLoader.loadLibrary("./", "zia-network");
    this->net.reset(this->moduleLoader.loadNetwork());
    if (!(this->net && this->net->config(config))) {
        return (false);
    }

    //TODO Load Pipeline's Modules
//    zia::api::ConfArray& moduleList =  std::get<zia::api::ConfArray>(conf["modules"].v);
//    std::string& modulesPath =  std::get<std::string>(conf["modulesPath"].v);
//    for (auto item : moduleList) {
//        try {
//            std::string module = std::get<std::string>(item.v);
            //TODO Pipeline.push_back("ModuleName", Module);
            //LoadModules
//                moduleLoader->loadLibrary(modulesPath, module);
//                pipeline->push_back(moduleLoader->loadModule())//[module] = libLoader().getModule(modulesPath + module);
            //pipeline[module].config(conf);
//        } catch (std::exception& err) {
//            std::cout << err.what() << std::endl;
//        }
//    }

    return (true);
}

bool Core::stop() {
    if (this->net.get()) {
        return (this->net->stop());
    }
    std::cerr << "No running Server" << std::endl;
    return (false);
}
