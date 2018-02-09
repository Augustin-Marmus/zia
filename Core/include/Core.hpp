//
// Created by marmus_a on 09/02/18.
//

#ifndef CPP_ZIA_CORE_HPP
#define CPP_ZIA_CORE_HPP


#include "Pipeline.hpp"
#include "ModuleLoader.hpp"
#include "FileWatcher.hpp"

class Core {
public:
    Core();
    ~Core();
    bool            run(const zia::api::Conf& config);
    bool            stop();

private:
    bool            config(const zia::api::Conf& config);

    Pipeline       pipeline;
    std::unique_ptr<zia::api::Net>  net;
    ModuleLoader   moduleLoader;
};


#endif //CPP_ZIA_CORE_HPP
