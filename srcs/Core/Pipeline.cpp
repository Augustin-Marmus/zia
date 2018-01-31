//
// Created by marmus_a on 27/01/18.
//

#include "Core/Pipeline.hpp"

void Pipeline::operator()(zia::api::Net::Raw msg, zia::api::NetInfo netInfo) {
    zia::api::HttpDuplex httpDuplex;

    httpDuplex.raw_req = msg;
    for (auto it = this->begin(); it != this->end(); it++) {
        it->second->exec(httpDuplex);
    }
}
