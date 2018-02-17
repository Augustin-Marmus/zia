//
// Created by louis on 10/02/18.
//

#ifndef             CPP_ZIA_CGI_HPP
#define             CPP_ZIA_CGI_HPP

#include            <api/module.h>
#include            <iostream>
#include            <cstring>
#include            <unistd.h>
#include            <sys/types.h>
#include            <sys/wait.h>
#include            <sys/stat.h>

#define             EOL     "\r\n"
#define             MAGICK  0xDEADBEEF

class               Ssl : public zia::api::Module {
public:
    Ssl();
    virtual         ~Ssl();
    virtual bool    config(const zia::api::Conf& conf);
    virtual bool    exec(zia::api::HttpDuplex& http);
private:
    const char      **createVirtualEnv(const zia::api::HttpRequest& req, const zia::api::NetInfo& net);
    const char      **mapToTab(const std::map<std::string, std::string>& env);
    bool            handleFather(int fd_in[2], int fd_out[2], pid_t pid, zia::api::HttpDuplex& http);
    bool            handleSon(zia::api::HttpDuplex& http, int fd_in[2],int fd_out[2], const char **env);
    bool            checkFile(const std::string& uri);
    void            sendResponse(std::string body, zia::api::HttpDuplex& http);
    const std::string     *getValueByKey(const std::string& key , const zia::api::Conf& conf);

        std::map<std::string, std::string>  _conf;
};

#endif              //CPP_ZIA_CGI_HPP
