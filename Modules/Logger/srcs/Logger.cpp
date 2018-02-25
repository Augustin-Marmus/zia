//
// Created by Pierre-Alexandre Monneau on 17/02/2018.
//

#include <fstream>
#include "Logger.hpp"

std::map<int, std::string> statusMap = {
        {(int)zia::api::http::common_status::continue_,                       "Continue"},
        {(int)zia::api::http::common_status::switching_protocols,             "Switching Protocols"},
        {(int)zia::api::http::common_status::ok,                              "OK"},
        {(int)zia::api::http::common_status::created,                         "Created"},
        {(int)zia::api::http::common_status::accepted,                        "Accepted"},
        {(int)zia::api::http::common_status::nonauthoritative_information,    "Non-Authorative Information"},
        {(int)zia::api::http::common_status::no_content,                      "No Content"},
        {(int)zia::api::http::common_status::reset_content,                   "Reset Content"},
        {(int)zia::api::http::common_status::partial_content,                 "Partial Content"},
        {(int)zia::api::http::common_status::multiple_choices,                "Multiple Choices"},
        {(int)zia::api::http::common_status::moved_permanently,               "Moved Permanently"},
        {(int)zia::api::http::common_status::found,                           "Found"},
        {(int)zia::api::http::common_status::see_other,                       "See Other"},
        {(int)zia::api::http::common_status::not_modified,                    "Not Modified"},
        {(int)zia::api::http::common_status::use_proxy,                       "Use Proxy"},
        {(int)zia::api::http::common_status::temporary_redirect,              "Temporary Redirect"},
        {(int)zia::api::http::common_status::bad_request,                     "Bad Request"},
        {(int)zia::api::http::common_status::unauthorized,                    "Unauthorized"},
        {(int)zia::api::http::common_status::payment_required,                "Payment Required"},
        {(int)zia::api::http::common_status::forbidden,                       "Forbidden"},
        {(int)zia::api::http::common_status::not_found,                       "Not Found"},
        {(int)zia::api::http::common_status::method_not_allowed,              "Method Not Allowed"},
        {(int)zia::api::http::common_status::not_acceptable,                  "Not Acceptable"},
        {(int)zia::api::http::common_status::proxy_authentication_required,   "Proxy Authentication Required"},
        {(int)zia::api::http::common_status::request_timeout,                 "Request Time-out"},
        {(int)zia::api::http::common_status::conflict,                        "Conflict"},
        {(int)zia::api::http::common_status::gone,                            "Gone"},
        {(int)zia::api::http::common_status::length_required,                 "Length Required"},
        {(int)zia::api::http::common_status::precondition_failed,             "Precondition Failed"},
        {(int)zia::api::http::common_status::request_entity_too_large,        "Request Entity Too Large"},
        {(int)zia::api::http::common_status::request_uri_too_large,           "Request-URI Too Long"},
        {(int)zia::api::http::common_status::unsupported_media_type,          "Unsupported Media Type"},
        {(int)zia::api::http::common_status::requested_range_not_satisfiable, "Requested range unsatisfiable"},
        {(int)zia::api::http::common_status::expectation_failed,              "Expectation failed"},
        {(int)zia::api::http::common_status::im_a_teapot,                     "I'm a teapot"},
        {(int)zia::api::http::common_status::internal_server_error,           "Internal Server Error"},
        {(int)zia::api::http::common_status::not_implemented,                 "Not Implemented"},
        {(int)zia::api::http::common_status::bad_gateway,                     "Bad Gateway"},
        {(int)zia::api::http::common_status::service_unavailable,             "Service Unavailable"},
        {(int)zia::api::http::common_status::gateway_timeout,                 "Gateway Time-out"},
        {(int)zia::api::http::common_status::http_version_not_supported,      "HTTP Version not supported"}
};

void Logger::initVecMethod()
{
    this->vecMethod.push_back(std::make_pair(0, "Unknown"));
    this->vecMethod.push_back(std::make_pair(1, "Options"));
    this->vecMethod.push_back(std::make_pair(2, "Get"));
    this->vecMethod.push_back(std::make_pair(3, "Head"));
    this->vecMethod.push_back(std::make_pair(4, "Post"));
    this->vecMethod.push_back(std::make_pair(5, "Put"));
    this->vecMethod.push_back(std::make_pair(6, "Delete_"));
    this->vecMethod.push_back(std::make_pair(7, "Trace"));
    this->vecMethod.push_back(std::make_pair(8, "Connect"));
}

Logger::Logger() {
    Logger::initVecMethod();
}

Logger::~Logger() {}

bool    Logger::setConf(const zia::api::Conf& conf) {
    if (conf.find("file") != conf.end()) {
        if (auto fileConf = std::get_if<bool>(&conf.at("file").v)) {
            if (*fileConf)
            {
                this->file = true;
            }
            else
                this->file = false;
        } else {
            std::cout << "ErrorConfig for file. File need a bool" << std::endl;
            return false;
        }
    } else {
        std::cout << "Cannot find  file config." << std::endl;
        return false;
    }
    if (conf.find("filePath") != conf.end()) {
        if (auto fileConf = std::get_if<std::string>(&conf.at("filePath").v)) {
            this->filepath = *fileConf;
            if (this->filepath.size() <= 0)
                return false;
        } else {
            std::cout << "ErrorConfig for filepath. filepath need a string" << std::endl;
            return false;
        }
    } else {
        std::cout << "Cannot find filepath config." << std::endl;
        return false;
    }
    if (conf.find("output") != conf.end()) {
        if (auto fileConf = std::get_if<bool>(&conf.at("output").v)) {
            if (*fileConf)
            {
                this->output = true;
            }
            else
                this->output = false;
        } else {
            std::cout << "ErrorConfig for output. Output need a bool" << std::endl;
            return false;
        }
    } else {
        std::cout << "Cannot find Output config." << std::endl;
        return false;
    }
    return true;
}

bool    Logger::config(const zia::api::Conf& conf) {
    if (!this->setConf(conf))
        return false;
    return (true);
}

void Logger::putOutputLog(zia::api::HttpDuplex& http) {
    std::cout << "REQUEST -> " << this->vecMethod[int (http.req.method)].second << " " << http.req.uri << std::endl;
}

void Logger::putFileLog(zia::api::HttpDuplex& http) {
    std::ofstream myFile(filepath);
    if (myFile.is_open())
        std::cout << "REQUEST -> " << this->vecMethod[int (http.req.method)].second << " " << http.req.uri << std::endl;
    else
        std::cout << "Unable to open file" << std::endl;
}

bool Logger::exec(zia::api::HttpDuplex& http) {
    std::cout << output << std::endl;
    if (output)
        putOutputLog(http);
    if (file)
        putFileLog(http);
    return true;
}

