//
// Created by abachelet on 17/02/18.
//

#ifndef CPP_ZIA_AUTHENTICATOR_HPP
#define CPP_ZIA_AUTHENTICATOR_HPP

#include    <sstream>
#include    "api/module.h"
#include    "api/http.h"
#include    "api/conf.h"

class       Authenticator : public zia::api::Module {
public:
    Authenticator();
    virtual ~Authenticator();

    virtual bool        config(const zia::api::Conf& conf);
    virtual bool        exec(zia::api::HttpDuplex& http);
    virtual bool        check_Auth(std::string hash);
    virtual std::string decode64(const std::string &val);

private:
    std::string login;
    std::string password;
};

#endif //CPP_ZIA_AUTHENTICATOR_HPP
