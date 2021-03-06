//
// Created by marmus_a on 09/02/18.
//

#include "Server.hpp"

Server::Server(const std::string &configFile) : core(nullptr) {
    std::cout << "     -----Welcome to RedTeam's Zia-----" << std::endl;
    this->configFile = configFile;
}

Server::~Server() {

}

bool Server::reloadConfig() {
    try {
        auto tmp = ConfParser(this->configFile).parse();
		if (tmp == NULL) {
            return false;
        }
        this->config.reset(tmp);
    } catch (const std::exception& err) {
        std::cerr << "Conf Error: "<< err.what() << std::endl;
        return (false);
    }
	return (true);
}

bool Server::run() {
    while (this->reloadConfig()) {
        FileWatcher watcher(this->configFile);
        this->core = std::make_unique<Core>();
		if (!this->core->run(*this->config)) {
			return (false);
		}
        std::cout << "Server is runnning" << std::endl;
        watcher.waitForModification();
        this->core->stop();
    }
    return false;
}
