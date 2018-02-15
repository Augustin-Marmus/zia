//
// Created by louis on 10/02/18.
//

#ifndef             CPP_ZIA_SSL_HPP
#define             CPP_ZIA_SSL_HPP

#include            <api/net.h>

class               Ssl : public zia::api::Net {
public:
    Ssl();
    virtual         ~Ssl();

    virtual bool    config(const zia::api::Conf& conf);
    virtual bool    run(zia::api::Net::Callback cb);
    virtual bool    stop();
    virtual bool    send(zia::api::ImplSocket* sock, const Raw& resp);
private:
};

#endif              //CPP_ZIA_SSL_HPP
