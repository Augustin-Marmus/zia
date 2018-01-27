//
// Created by marmus_a on 27/01/18.
//

#ifndef CPP_ZIA_PIPELINE_HPP
#define CPP_ZIA_PIPELINE_HPP

#include <bits/unique_ptr.h>
#include "api/module.h"

class Pipeline : std::map<std::string, std::unique_ptr<zia::api::Module>>{
public:
    Pipeline() = default;
    ~Pipeline() = default;

    void    operator()(zia::api::Net::Raw, zia::api::NetInfo);
};


#endif //CPP_ZIA_PIPELINE_HPP
