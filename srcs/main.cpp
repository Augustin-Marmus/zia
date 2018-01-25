//
// Created by marmus_a on 25/01/18.
//

#include <iostream>
#include "Network/UnixSocket.hpp"

int main(int ac, char **av) {
    if (ac > 1) {
        ISocket *sock = new UnixSocket();
        sock->bind(std::string("0.0.0.0"), av[1]);
        sock->listen();
        ISocket *client = new UnixSocket();
        sock->accept(*client);
        std::string buff;
        client->read(buff);
        std::cout << buff << std::endl  ;
        client->send(std::string("OK"));
        std::cout << "nice" << std::endl;
    } else {
        std::cout << av[0] << " port" << std::endl;
    }
}