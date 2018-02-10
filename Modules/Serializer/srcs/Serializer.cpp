//
// Created by Elias Demnati on 10/02/2018.
//

#include    "Serializer.hpp"

bool        Serializer::config(const zia::api::Conf& conf) {
    return true;
}

bool        Serializer::exec(zia::api::HttpDuplex& http) {
    return true;
}
