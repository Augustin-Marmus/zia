//
// Created by marmus_a on 25/01/18.
//

#include <iostream>
#include <memory>
#include <unistd.h>
#include <Core/Pipeline.hpp>
#include <Core/IModuleLoader.hpp>
#include <Core/UnixModuleLoader.hpp>
#include <thread>

int main(int ac, char **av) {
    if (ac > 1) {
        Pipeline        pipeline;
        std::shared_ptr<IModuleLoader>   moduleLoader(new UnixModuleLoader());
        char buff[4096];
        getcwd(buff, 4096);
        std::cout << "Working Directory: " << buff << std::endl;
        //TODO Config          config("path");

        //          Config en dur TMP
        zia::api::Conf conf;
        zia::api::ConfArray tmp;
        zia::api::ConfArray tmp2;
        tmp.emplace_back(zia::api::ConfValue());
        tmp[0].v = std::string("zia-serializer");
        conf["port"].v = std::string("4242");
        conf["netModule"].v = std::string("test");
        conf["modules"].v = tmp;
        conf["modulesPath"].v = std::string("./lib/");
        //          end

        zia::api::ConfArray& moduleList =  std::get<zia::api::ConfArray>(conf["modules"].v);
        std::string& modulesPath =  std::get<std::string>(conf["modulesPath"].v);
        for (auto item : moduleList) {
            try {
                std::string module = std::get<std::string>(item.v);
                //TODO Pipeline.push_back("ModuleName", Module);
                //LoadModules
//                moduleLoader->loadLibrary(modulesPath, module);
//                pipeline->push_back(moduleLoader->loadModule())//[module] = libLoader().getModule(modulesPath + module);
                //pipeline[module].config(conf);
            } catch (std::exception& err) {
                std::cout << err.what() << std::endl;
            }
        }

        moduleLoader->loadLibrary(std::string("./"), std::string("zia-network"));
        std::unique_ptr<zia::api::Net> net(moduleLoader->loadNetwork());

        if (net && net->config(conf) && net->run(pipeline)) {
            std::chrono::seconds s(120);
            std::this_thread::sleep_for(s);
            net->stop();
        }
//        net.reset(moduleLoader->loadNetwork());
//       if (net->config(conf) && net->run(pipeline)) {
//            std::chrono::seconds s(5);
//            std::this_thread::sleep_for(s);
//            net->stop();
//        } net->stop();
        //net.run(pipeline);
    } else {
        std::cout << "usage: " << av[1] << " pathToConfigurationFile" << std::endl;
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