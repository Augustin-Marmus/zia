//
// Created by Elias Demnati on 10/02/2018.
//

#include    <iostream>
#include    <regex>
#include    "Serializer.hpp"

std::map<std::string, zia::api::http::Version> versionMap = {
  {"HTTP/0.9", zia::api::http::Version::http_0_9},
  {"HTTP/1.0", zia::api::http::Version::http_1_0},
  {"HTTP/1.1", zia::api::http::Version::http_1_1},
  {"HTTP/2.0", zia::api::http::Version::http_2_0}
};

std::map<std::string, zia::api::http::Method> methodMap = {
  {"OPTIONS", zia::api::http::Method::options},
  {"GET",     zia::api::http::Method::get},
  {"HEAD",    zia::api::http::Method::head},
  {"POST",    zia::api::http::Method::post},
  {"PUT",     zia::api::http::Method::put},
  {"DELETE",  zia::api::http::Method::delete_},
  {"TRACE",   zia::api::http::Method::trace},
  {"CONNECT", zia::api::http::Method::connect}
};

bool        Serializer::config(const zia::api::Conf& conf) {
    return true;
}

bool        Serializer::parseMethodVersionUri(zia::api::HttpDuplex& http) {
  const std::regex  mvuRegex("((?:.*)) ((?:.*)) ((?:.*))");
  std::string       line;
  std::smatch       match;

  getline(this->reqStream, line);
  if (std::regex_match(line, match, mvuRegex) && match.size() == 4) {
    for (size_t i = 1; i < match.size(); ++i) {
      if (i == 1) http.req.method = methodMap.find(match[i].str()) != methodMap.end() ? methodMap[match[i].str()] : zia::api::http::Method::unknown;
      if (i == 2) http.req.uri = match[i].str();
      if (i == 3) http.req.version = versionMap.find(match[i].str()) != versionMap.end() ? versionMap[match[i].str()] : zia::api::http::Version::unknown;
    }
    return true;
  }

  return false;
}

bool        Serializer::parseHeaders(zia::api::HttpDuplex& http) {
  const std::regex headerRegex("((?:.*)): ((?:.*))");
  std::string      line;
  std::smatch      match;

  while (getline(this->reqStream, line) && std::regex_match(line, match, headerRegex)) {
    http.req.headers[match[1].str()] = match[2].str();
  }

  return true;
}

bool        Serializer::parseBody(zia::api::HttpDuplex& http) {
  std::string   line;

  while (getline(this->reqStream, line)) {
    for (auto it: line) {
      http.req.body.push_back(static_cast<std::byte>(it));
    }
  }

  return true;
}

bool        Serializer::exec(zia::api::HttpDuplex& http) {
    std::string   convertedString;

    std::cout << "exec serializer " << std::endl;
    for (auto& it: http.raw_req) {
      convertedString += static_cast<char>(it);
    }
    this->reqStream.str(convertedString);

    return this->parseMethodVersionUri(http) && this->parseHeaders(http) && this->parseBody(http);
}
