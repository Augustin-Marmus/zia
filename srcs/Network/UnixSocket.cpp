//
// Created by marmus_a on 25/01/18.
//

#include "../../include/Network/UnixSocket.hpp"

UnixSocket::UnixSocket() {
    struct protoent *proto;

    if (!(proto = ::getprotobyname("TCP"))) {
        std::cerr << "Failed to find TCP protocol" << std::endl;
    } else {
        if ((this->socket = ::socket(AF_INET, SOCK_STREAM, proto->p_proto)) < 1) {
            std::cerr << "Failed to open socket" << std::endl;
        }
    }
}

bool UnixSocket::bind(const std::string &addr, const std::string &port) {
    this->bind(addr, std::stoi(port));
}

bool UnixSocket::bind(const std::string &addr, int port) {
    this->addr.sin_family = AF_INET;
    this->addr.sin_port = htons(port);
    this->addr.sin_addr.s_addr = INADDR_ANY;
    if (::bind(this->socket, (const struct sockaddr *)(&this->addr), sizeof(this->addr)) == -1)
    {
        perror("bind: ");
        return (false);
    }
    return (true);
}

bool UnixSocket::listen() {
    return (!::listen(this->socket, UnixSocket::MAXQUEUE));
}

bool UnixSocket::accept(ISocket &socket) {
    socklen_t addrLen;
    auto unixSocket = dynamic_cast<UnixSocket *>(&socket);
    if (unixSocket) {
        if ((unixSocket->socket = ::accept(this->socket, (struct sockaddr *)&unixSocket->addr, &addrLen)) < 0) {
            std::cerr << "Fail to accept " << inet_ntoa(unixSocket->addr.sin_addr) << std::endl;
            return (false);
        }
        return (true);
    }
    return (false);
}

bool UnixSocket::close() {
    return(!::close(this->socket));
}

int UnixSocket::send(const std::string &str) {
    return (::send(this->socket, str.c_str(), str.size(), 0));
}

int UnixSocket::read(std::string &buff) {
    char   buffer[4096];
    int    res;

    res = recv(this->socket, &buffer, 4096, 0);
    buffer[res] = 0;
    buff = buffer;
    return (res);
}
