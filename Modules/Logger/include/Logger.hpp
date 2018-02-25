//
// Created by Pierre-Alexandre Monneau on 17/02/2018.
//

#ifndef CPP_ZIA_LOGGER_HPP
#define CPP_ZIA_LOGGER_HPP

#include <iostream>
#include <api/module.h>
#include <vector>

class Logger : public zia::api::Module {
public:
    Logger();
    virtual ~Logger();
    virtual bool    config(const zia::api::Conf& conf);
    virtual bool    exec(zia::api::HttpDuplex& http);

private:
    std::vector<std::pair<int, std::string>> vecMethod;
    bool file;
    std::string filepath;
    bool output;
    bool setConf(const zia::api::Conf& conf);
    void putOutputLog(zia::api::HttpDuplex& http);
    void initVecMethod();
    void putFileLog(zia::api::HttpDuplex& http);
};

#endif //CPP_ZIA_LOGGER_HPP