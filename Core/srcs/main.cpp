//
// Created by marmus_a on 25/01/18.
//

#include <iostream>
#include <memory>
#include <thread>
#include <FileWatcher.hpp>
#include <Server.hpp>
#include "Pipeline.hpp"
#include "ModuleLoader.hpp"

int main(int ac, char **av) {
    if (ac > 1) {
        return (Server(std::string(av[1])).run());
    } else {
        std::cout << "usage: " << av[0] << " pathToConfigurationFile" << std::endl;
        return (true);
    }
}
