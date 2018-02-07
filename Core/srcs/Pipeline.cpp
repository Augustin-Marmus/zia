//
// Created by marmus_a on 27/01/18.
//

#include "Pipeline.hpp"

Pipeline::Pipeline(int nbWorkers) {
    this->pool = new ThreadPool(nbWorkers);
}

Pipeline::~Pipeline() {
    delete this->pool;
    this->pool = nullptr;
}

void Pipeline::run(zia::api::Net::Raw req, zia::api::NetInfo netInfo) const {
    this->pool->runAsync([this, req, netInfo] {
        zia::api::HttpDuplex httpDuplex;

        std::string tmp;
        for (auto c : req) {
            tmp.push_back(static_cast<char>(c));
        }
        std::cout << "[" << netInfo.ip.str << ":" << netInfo.port << "]: " << tmp << std::flush;
        httpDuplex.raw_req = req;
        for (auto it = this->begin(); it != this->end(); it++) {
            it->second->exec(httpDuplex);
        }
    });
}

zia::api::Net::Callback Pipeline::getCallback() const {
    return ([this](zia::api::Net::Raw req, zia::api::NetInfo netInfo) {this->run(req, netInfo);});
}
