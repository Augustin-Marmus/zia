//
// Created by marmus_a on 27/01/18.
//

#ifndef CPP_ZIA_PIPELINE_HPP
#define CPP_ZIA_PIPELINE_HPP

#include <memory>
#include "api/module.h"

class Pipeline : public std::map<std::string, std::shared_ptr<zia::api::Module>>{
public:
    Pipeline() = default;
    ~Pipeline() = default;

    void    operator()(zia::api::Net::Raw, zia::api::NetInfo);
};


#endif //CPP_ZIA_PIPELINE_HPP
