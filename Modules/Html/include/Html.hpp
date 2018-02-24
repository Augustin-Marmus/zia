//
// Created by Elias Demnati on 16/02/2018.
//

#ifndef     CPP_ZIA_HTML_HPP
#define     CPP_ZIA_HTML_HPP

#include    <fstream>
#include    "api/module.h"
#include    "api/http.h"
#include    "api/conf.h"

class       Html : public zia::api::Module {
public:
    Html() = default;
    virtual ~Html() = default;

    virtual bool    config(const zia::api::Conf& conf);
    virtual bool    exec(zia::api::HttpDuplex& http);
    bool            checkUriAndRequest(zia::api::HttpDuplex& html, std::ifstream& fileStream);
    bool            getFile(zia::api::HttpDuplex& html, std::ifstream& fileStream);
private:
  std::string   htmlFolderPath;
};

#endif              //CPP_ZIA_HTML_HPP
