//
// Created by marmus_a on 30/01/18.
//

#include "Network/Network.hpp"

Network::Network() : listener(new Socket), sockets(), thread(nullptr) {

}

Network::~Network() {
    for (auto &socket : this->sockets) {
        if (socket->isOpen()) {
            socket->close();
        }
    }
    if (this->listener->isOpen()) {
        this->listener->close();
    }
}

bool Network::config(const zia::api::Conf &conf) {
    return (this->listener->bind(std::string("0.0.0.0"), 1337));
}

bool Network::run(zia::api::Net::Callback cb) {
    std::cout << "Running Network class" << std::endl;
    std::shared_ptr<ISocket>     connexion(new Socket);

    this->listener->listen();
    this->callback = cb;
    //TODO segfault ici
    this->thread = std::make_unique<std::thread>(networkRoutine, this);
    return (true);
}

bool Network::stop() {
    std::cout << "Stopping Network class" << std::endl;
    this->listener->close();
    if (this->thread) {
        this->thread->join();
        this->thread.reset();
        this->thread = nullptr;
    }
    return (true);
}

bool Network::send(zia::api::ImplSocket *sock, const zia::api::Net::Raw &resp) {
    std::string     tmp;
    for (auto c : resp) {tmp += static_cast<char>(c);}
    std::cout << "Sending [" << tmp << "] Network class" << std::endl;
    for (auto& socket : this->sockets) {
        socket->send(tmp);
    }
    return (true);
}

int Network::setFdsSet() {
    int         socketMax;
    FD_ZERO(&this->fdsSet);
    FD_SET(this->listener->getSocket(), &this->fdsSet);
    socketMax = this->listener->getSocket();
    for (auto& socket : this->sockets) {
        FD_SET(socket->getSocket(), &this->fdsSet);
        socketMax = ((socket->getSocket() > socketMax) ? (socket->getSocket()) : (socketMax));
    }
    return (socketMax + 1);
}

void networkRoutine(Network* net) {
    struct timeval time;
    while (net->listener->isOpen()) {
        time = {1, 0};
        if (::select(net->setFdsSet(), &net->fdsSet, nullptr, nullptr, &time) >= 0) {
            for (auto connexion : net->sockets) {
                if (FD_ISSET(connexion->getSocket(), &net->fdsSet)) {
                    std::string msg;
                    connexion->recv(msg);
                    if (!msg.empty()) {
                        std::cout << "[" << net->sockets.size() << "]" << *connexion << " : " << msg << std::flush;
                        connexion->send(msg);
                    } else {
                        connexion->close();
                    }
                }
            }

            net->sockets.remove_if([](std::shared_ptr<ISocket> &socket) {
                return (!socket->isOpen());
            });

            if (FD_ISSET(net->listener->getSocket(), &net->fdsSet) && net->listener->isOpen()) {
                std::shared_ptr<Socket> connexion = std::make_shared<Socket>();
                if (net->listener->accept(*connexion)) {
                    net->sockets.push_back(connexion);
                }
            }
        } else {
            perror("select");
        }
    }

    net->sockets.erase(net->sockets.begin(), net->sockets.end());
    //net->sockets.remove_if([] (std::shared_ptr<ISocket>& socket) {return (true);});
    return;
}