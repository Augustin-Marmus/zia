//
// Created by marmus_a on 09/02/18.
//

#include "Server.hpp"

Server::Server(const std::string &configFile) {
    this->configFile = configFile;
}

Server::~Server() {

}

bool Server::reloadConfig() {
    try {
        this->config.reset(ConfParser(this->configFile).parse());
    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        return (false);
    }
    /*zia::api::Conf conf;
    zia::api::ConfArray tmp;
    zia::api::ConfArray tmp2;
    tmp.emplace_back(zia::api::ConfValue());
    tmp[0].v = std::string("zia-serializer");
    conf["port"].v = std::string("4242");
    conf["netModule"].v = std::string("test");
    conf["modules"].v = tmp;
    conf["modulesPath"].v = std::string("./lib/");*/
	return (true);
}

bool Server::run() {
    while (this->reloadConfig()) {
        FileWatcher watcher(this->configFile);
        this->core = std::make_unique<Core>();
		if (!this->core->run(*this->config)) {
			return (false);
		}
        watcher.waitForModification();
        this->core->stop();
    }
    return false;
}
