//
// Created by marmus_a on 29/01/18.
//

#include <Network/Network.hpp>
#include <iostream>

extern "C" {
    zia::api::Net*      getNetwork() {
        return (new Network());
    }
}