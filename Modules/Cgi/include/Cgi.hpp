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

class               Cgi : public zia::api::Module {
public:
    Cgi();
    virtual         ~Cgi();
    virtual bool    config(const zia::api::Conf& conf);
    virtual bool    exec(zia::api::HttpDuplex& http);
private:
    const char      **createVirtualEnv(const zia::api::HttpRequest& req, const zia::api::NetInfo& net);
    const char      **mapToTab(const std::map<std::string, std::string>& env);
    bool            handleFather(int fd[2], pid_t pid, zia::api::HttpDuplex& http);
    bool            handleSon(zia::api::HttpDuplex& http, int fd[2], const char **env);
    bool            checkFile(const std::string& uri);
    void            sendResponse(std::string body);
};

#endif              //CPP_ZIA_CGI_HPP
