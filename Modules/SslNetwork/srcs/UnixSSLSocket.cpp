//
// Created by marmus_a on 25/01/18.
//

#include "UnixSSLSocket.hpp"

UnixSSLSocket::UnixSSLSocket() {
    struct protoent *proto;

    this->opened = false;
    this->netInfo.sock = this;
    if (!(proto = ::getprotobyname("TCP"))) {
        std::cerr << "Failed to find TCP protocol" << std::endl;
    } else {
        if ((this->socket = ::socket(AF_INET, SOCK_STREAM, proto->p_proto)) < 0) {
            std::cerr << "Failed to open socket" << std::endl;
        }
    }
}

UnixSSLSocket::~UnixSSLSocket() {
    this->close();
}

bool UnixSSLSocket::bind(const std::string &addr, const std::string &port) {
    return (this->bind(addr, std::stoi(port)));
}

bool UnixSSLSocket::bind(const std::string &addr, int port) {
    this->addr.sin_family = AF_INET;
    this->addr.sin_port = htons(port);
    this->addr.sin_addr.s_addr = INADDR_ANY;
    if (::bind(this->socket, (const struct sockaddr *)(&this->addr), sizeof(this->addr)) < 0)
    {
        perror("bind");
        return (false);
    }
    this->netInfo.port = port;
    this->netInfo.ip.i = this->addr.sin_addr.s_addr;
    this->netInfo.ip.str = ::inet_ntoa(this->addr.sin_addr);
    return (true);
}

bool UnixSSLSocket::listen() {
    this->opened = true;
    this->netInfo.time = std::chrono::system_clock::now();
    return (!::listen(this->socket, UnixSSLSocket::MAXQUEUE));
}

bool UnixSSLSocket::accept(zia::api::ImplSocket &socket) {
    socklen_t addrLen;
    auto unixSocket = dynamic_cast<UnixSSLSocket *>(&socket);
    if (unixSocket) {
        if ((unixSocket->socket = ::accept(this->socket, (struct sockaddr *)&unixSocket->addr, &addrLen)) < 0) {
            std::cerr << "Fail to accept " << inet_ntoa(unixSocket->addr.sin_addr) << std::endl;
            return (false);
        }
        unixSocket->netInfo.ip.i = unixSocket->addr.sin_addr.s_addr;
        unixSocket->netInfo.ip.str = ::inet_ntoa(unixSocket->addr.sin_addr);
        unixSocket->netInfo.port = this->netInfo.port;
        unixSocket->netInfo.time = std::chrono::system_clock::now();
        unixSocket->opened = true;
        //TODO Handshake with SSL Certificate
        return (true);
    }
    return (false);
}

bool UnixSSLSocket::close() {
    this->opened = false;
    return(!::close(this->socket));
}

int UnixSSLSocket::send(const std::string &str) {
    //TODO Socket encryption
    return (::send(this->socket, str.c_str(), str.size(), 0));
}

int UnixSSLSocket::recv(std::string &buff) {
    char   buffer[4096];
    int    res;

    //TODO Socket Decryption
    res = ::recv(this->socket, &buffer, 4096, 0);
    buffer[res] = 0;
    buff = buffer;
    return (res);
}

int UnixSSLSocket::getSocket() const {
    return {this->socket};
}

bool UnixSSLSocket::isOpen() const {
    return this->opened;
}

const zia::api::NetInfo &UnixSSLSocket::getInfo() const {
    return (this->netInfo);
}