//
// Created by marmus_a on 25/01/18.
//

#include <iostream>
#include <bits/unique_ptr.h>
#include <Core/Pipeline.hpp>
#include "Network/UnixSocket.hpp"

int main(int ac, char **av) {
    if (ac > 1) {
        Pipeline        pipeline;
        //TODO Load .so / .dll into net
        //zia::api::Net   net;

        //TODO Pipeline.push_back("ModuleName", Module);
        //LoadModules
        //ConfModules
        //net.config()
        //net.run(pipeline);
    } else {
        std::cerr << "usage: " << av[1] << " pathToConfigurationFile" << std::endl;
    }
//    if (ac > 1) {
//        std::unique_ptr<ISocket> listener(new UnixSocket());
//        listener->bind(std::string("0.0.0.0"), av[1]);
//        listener->listen();
//        while(1)
//        {
//            std::cout << "Server is listening..." << std::endl;
//            std::unique_ptr<ISocket> connexion(new UnixSocket());
//
//            listener->accept(*connexion);
//
//            while(1)
//            {
//                std::string msg;
//                connexion->recv(msg);
//                std::cout << *connexion << " : " << msg << std::endl;
//
//                connexion->send(msg);
//            }
//        }
//    } else {
//        std::cout << av[0] << " port" << std::endl;
//    }
}