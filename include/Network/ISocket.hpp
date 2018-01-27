//
// Created by marmus_a on 25/01/18.
//

#ifndef CPP_ZIA_ISOCKET_HPP
#define CPP_ZIA_ISOCKET_HPP

#include "api/net.h"

//class zia::api::ImplSocket {};

class ISocket /*: public zia::api::ImplSocket */{
public:
    virtual bool            bind(const std::string& addr, const std::string& port) = 0;
    virtual bool            bind(const std::string& addr, int port) = 0;
    virtual bool            listen() = 0;
    virtual bool            accept(ISocket& socket) = 0;
    virtual bool            close() = 0;

    virtual int             send(const std::string& str) = 0;
    virtual int             recv(std::string& buff) = 0;
};

class zia::api::ImplSocket : public ISocket {};

#endif //CPP_ZIA_ISOCKET_HPP
