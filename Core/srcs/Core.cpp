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
    if (!this->config(config) || !this->pipeline) {
        std::cerr << "Failed to configure Core" << std::endl;
        return (false);
    }
    return (this->net->run(this->pipeline->getCallback()));
}

bool Core::config(const zia::api::Conf& config) {
    try {
        this->pipeline = std::make_shared<Pipeline>(4/* get Conf nbWorkers*/);
        this->moduleLoader.loadLibrary("./", "zia-network");
        this->net.reset(this->moduleLoader.loadNetwork());
        if (auto netConfig = std::get_if<zia::api::Conf>(&config.at("Net").v)) {
            if (auto netInternConfig = std::get_if<zia::api::Conf>(&netConfig->at("config").v)) {
                if (!this->net || !this->net->config(*netInternConfig)) {
                    return (false);
                }
            } else {
                std::cout << "Error: Missing config in Module Net" << std::endl;
                return (false);
            }
        } else {
            std::cout << "Error: Missing module Net in configuration file" << std::endl;
            return (false);
        }

        //TODO Load Pipeline's Modules
        if (auto moduleList = std::get_if<zia::api::ConfArray>(&config.at("Modules").v)) {
            for (auto item : *moduleList) {
                const zia::api::Conf *moduleConf;
                const zia::api::Conf *moduleInternConfig;
                std::string path;
                const std::string *name;
                const std::string *lib;
                if (!(moduleConf = std::get_if<zia::api::Conf>(&item.v))) {
                    std::cerr << "Error: bad Module conf type" << std::endl;
                    return (false);
                }
//            if (auto tmpPath = std::get_if<std::string>(&moduleConf->at("path").v)) {
//                path = *tmpPath;
//            } else {
                path = "";
//            }
                if (!(name = std::get_if<std::string>(&moduleConf->at("name").v))) {
                    std::cerr << "Error: Missing field name in a Module" << std::endl;
                    return (false);
                }
                if (!(lib = std::get_if<std::string>(&moduleConf->at("lib").v))) {
                    std::cerr << "Error: Missing field lib in Module " << *name << std::endl;
                    return (false);
                }
                if (!(moduleInternConfig = std::get_if<zia::api::Conf>(&moduleConf->at("config").v))) {
                    std::cerr << "Error: Missing config of Module " << *name << std::endl;
                    return (false);
                }
                if (!this->moduleLoader.loadLibrary(path, *lib)) {
                    std::cerr << "Error: Unable to load Library " << path << *lib << std::endl;
                }
                if (zia::api::Module *loadedModule = this->moduleLoader.loadModule()) {
                    if (!loadedModule->config(*moduleInternConfig)) {
                        std::cerr << "Error: Configuration of module " << *name << " failed" << std::endl;
                        return (false);
                    }
                    this->pipeline->insert(this->pipeline->end(),
                                           std::pair<std::string, std::shared_ptr<zia::api::Module>>(*name,
                                                                                                     std::shared_ptr<zia::api::Module>(
                                                                                                             loadedModule)));
                } else {
                    std::cerr << "Error: can't load module from library " << path << *lib << std::endl;
                    return (false);
                }
            }
            return (true);
        } else {
            std::cerr << "Error: Missing field Modules in configuration" << std::endl;
            return (false);
        }
    } catch(std::exception& err) {
        std::cerr << err.what() << std::endl;
        return (false);
    }
}

bool Core::stop() {
    if (this->net.get()) {
        return (this->net->stop());
    }
    std::cerr << "No running Server" << std::endl;
    return (false);
}
