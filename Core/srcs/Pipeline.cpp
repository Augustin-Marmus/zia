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

void Pipeline::run(zia::api::Net::Raw req, zia::api::NetInfo netInfo, zia::api::Net& network) const {
    this->pool->runAsync([this, req, netInfo, &network] {
        zia::api::HttpDuplex httpDuplex;
        std::string tmp;

        for (auto c : req) {
            tmp.push_back(static_cast<char>(c));
        }
        std::cout << "[" << netInfo.ip.str << ":" << netInfo.port << "]: " << tmp << std::flush;
        httpDuplex.raw_req = req;
        httpDuplex.raw_resp = req;
        for (auto& it : *this){
            if (!it->exec(httpDuplex)){
                break;
            }
        }
        network.send(netInfo.sock, httpDuplex.raw_resp);
        if (httpDuplex.resp.headers.find("Connection") != httpDuplex.resp.headers.end()
            && httpDuplex.resp.headers["Connection"] == "close") {
            netInfo.sock->close();
        }
    });
}

zia::api::Net::Callback Pipeline::getCallback(zia::api::Net& network) const {
    return ([this, &network](zia::api::Net::Raw req, zia::api::NetInfo netInfo) {this->run(req, netInfo, network);});
}
