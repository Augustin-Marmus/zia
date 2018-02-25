//
// Created by abachelet on 17/02/18.
//

#include <iostream>
#include "Authenticator.hpp"

static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ""abcdefghijklmnopqrstuvwxyz""0123456789+/";

Authenticator::Authenticator() {
}

Authenticator::~Authenticator() {

}

bool Authenticator::config(const zia::api::Conf &conf) {
    if (conf.find("login") != conf.end()) {
        if (auto tmpLogin = std::get_if<std::string>(&conf.at("login").v)) {
            this->login = *tmpLogin;
        } else {
            std::cerr << "Error: Login field is not a string in configuration" << std::endl;
            return (false);
        }
    } else {
        std::cerr << "Error: Failed to reach login in configuration" << std::endl;
        return (false);
    }
    if (conf.find("password") != conf.end()) {
        if (auto tmpPass = std::get_if<std::string>(&conf.at("password").v)) {
            this->password = *tmpPass;
        } else {
            std::cerr << "Error: Password field is not a string in configuration" << std::endl;
            return (false);
        }
    } else {
        std::cerr << "Error: Failed to reach password in configuration" << std::endl;
        return (false);
    }
    return true;
}

bool Authenticator::exec(zia::api::HttpDuplex &http) {
    if (http.req.method == zia::api::http::Method::get) {
        if (http.req.headers.find("Authorization") != http.req.headers.end() && check_Auth(http.req.headers["Authorization"])) {
            return true;
        }
        else {
            http.resp.version = http.req.version;
            http.resp.headers["WWW-Authenticate"] = "Basic realm=\"Access to the staging site\"";
            http.resp.headers["Connection"] = "close";
            http.resp.status = zia::api::http::common_status::unauthorized;
        }
    }
    else {
        http.resp.version = http.req.version;
        http.resp.status = zia::api::http::common_status::forbidden;
    }
    return false;
}


static inline bool is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string Authenticator::decode64(const std::string &val) {
    size_t in_len = val.size();
    size_t i = 0;
    size_t j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;
    while (in_len-- && ( val[in_] != '=') && is_base64(val[in_])) {
        char_array_4[i++] = val[in_]; in_++;
        if (i ==4) {
            for (i = 0; i <4; i++)
                char_array_4[i] = static_cast<unsigned char>(base64_chars.find(char_array_4[i]));
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }
    if (i) {
        for (j = i; j <4; j++)
            char_array_4[j] = 0;
        for (j = 0; j <4; j++)
            char_array_4[j] = static_cast<unsigned char>(base64_chars.find(char_array_4[j]));
        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }
    return ret;
}

bool Authenticator::check_Auth(std::string hash) {
   if (hash.substr(0,6) == "Basic ") {
        hash = decode64(hash.substr(6));
        std::size_t pos = hash.find(":");
        std::string login = hash.substr(0, pos);
        std::string pass = hash.substr(pos + 1);
       if (login == this->login && pass == this->password) {
            return (true);
        }
    }
    return (false);
}