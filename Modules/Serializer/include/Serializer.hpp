//
// Created by Elias Demnati on 10/02/2018.
//

#ifndef     CPP_ZIA_SERIALIZER_HPP
#define     CPP_ZIA_SERIALIZER_HPP

#include    <sstream>
#include    "api/module.h"
#include    "api/http.h"
#include    "api/conf.h"

class       Serializer : public zia::api::Module {
public:
    Serializer() = default;
    virtual ~Serializer() = default;

    virtual bool    config(const zia::api::Conf& conf);
    virtual bool    exec(zia::api::HttpDuplex& http);
    bool            parseMethodVersionUri(zia::api::HttpDuplex& http);
    bool            parseHeaders(zia::api::HttpDuplex& http);
    bool            parseBody(zia::api::HttpDuplex& http);
private:
    std::istringstream     reqStream;
};

#endif              //CPP_ZIA_SERIALIZER_HPP
