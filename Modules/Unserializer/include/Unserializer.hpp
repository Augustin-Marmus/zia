//
// Created by Elias Demnati on 10/02/2018.
//

#ifndef     CPP_ZIA_UNSERIALIZER_HPP
#define     CPP_ZIA_UNSERIALIZER_HPP

#include    <sstream>
#include    "api/module.h"
#include    "api/http.h"
#include    "api/conf.h"

class       Unserializer : public zia::api::Module {
public:
    Unserializer() = default;
    virtual ~Unserializer() = default;

    virtual bool    config(const zia::api::Conf& conf);
    virtual bool    exec(zia::api::HttpDuplex& http);
    bool            setResponse(zia::api::HttpDuplex& http);
    bool            convertToByte(zia::api::HttpDuplex& http);
private:
    std::stringstream   ss;
};

#endif              //CPP_ZIA_UNSERIALIZER_HPP
