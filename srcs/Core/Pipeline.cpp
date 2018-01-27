//
// Created by marmus_a on 27/01/18.
//

#include <Network/ISocket.hpp>
#include "Core/Pipeline.hpp"

void Pipeline::operator()(zia::api::Net::Raw msg, zia::api::NetInfo netInfo) {
    std::unique_ptr<zia::api::HttpDuplex> httpDuplex(new zia::api::HttpDuplex);

    httpDuplex->raw_req = msg;
    for (auto it = this->begin(); it != this->end(); it++) {
        if (it->first != "Serializer") {
            it->second->exec(*httpDuplex);
        }
    }
}
