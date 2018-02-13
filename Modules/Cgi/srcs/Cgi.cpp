//
// Created by louis on 10/02/18.
//

#include "Cgi.hpp"

Cgi::Cgi()
{}

Cgi::~Cgi()
{}


const char **Cgi::mapToTab(const std::map<std::string, std::string>& env)
{
    const char **vEnv = new const char *[env.size() + 1];
    int i = -1;

    for (auto &it : env) {
        vEnv[++i] = strdup(std::string(it.first + "=" + it.second).c_str());
    }
    vEnv[i] = NULL;
    return vEnv;
}

bool        Cgi::checkFile(const std::string& rUri)
{
    std::string tmp, uri;

    uri = rUri;
    if (uri.find("?") != uri.npos) {
        uri = uri.substr(0, uri.find("?"));
    }
    if (uri.find("/cgi-bin/") != uri.npos) {
        //script = uri.substr(uri.find("/cgi-bin/"));
    }
}

const char **Cgi::createVirtualEnv(const zia::api::HttpRequest& req, const zia::api::NetInfo& net)
{
    std::map<std::string, std::string>  env;
    std::string query, uri, script, cgiDir;
    struct stat  st;

    //TODO: find values in server's config
    env["DOCUMENT_ROOT"] = "/home/louis/tek3/cpp_zia";
    env["SERVER_NAME"] = "127.0.0.1";
        env["SERVER_PROTOCOL"] = "HTTP/1.1";
    env["SERVER_PORT"] = "80";
    env["SERVER_ADDR"] = "127.0.0.1";
    env["SERVER_SOFTWARE"] = "zia-redteam1.1";
    cgiDir = "/cgi-bin";

    if (std::getenv("PATH")) {  env["PATH"] = std::getenv("PATH"); }
    if (std::getenv("HOME")) {  env["HOME"] = std::getenv("HOME"); }

    //TODO: find values in req
    env["REQUEST_METHOD"] = "post";
    env["REQUEST_URI"] = req.uri;
    if (req.headers.find("Accept") != req.headers.end())
        env["HTTP_ACCEPT"] = req.headers.at("Accept");
    if (req.headers.find("Accept-Encoding") != req.headers.end())
        env["HTTP_ACCEPT_ENCODING"] = req.headers.at("Accept-Encoding");
    if (req.headers.find("Accept-Language") != req.headers.end())
        env["HTTP_ACCEPT_LANGUAGE"] = req.headers.at("Accept-Language");
    if (req.headers.find("Accept-Charset") != req.headers.end())
        env["HTTP_ACCEPT_CHARSET"] = req.headers.at("Accept-Charset");
    if (req.headers.find("Connection") != req.headers.end())
        env["HTTP_CONNECTION"] = req.headers.at("Connection");
    if (req.headers.find("Host") != req.headers.end())
        env["HTTP_HOST"] = req.headers.at("Host");
    if (req.headers.find("User-Agent") != req.headers.end())
        env["HTTP_USER_AGENT"] = req.headers.at("User-Agent");
    if (req.headers.find("Content-Length") != req.headers.end())
        env["CONTENT_LENGTH"] = req.headers.at("Content-Length");
    else
        env["CONTENT_LENGTH"] = "0";
    if (req.headers.find("Content-Type") != req.headers.end())
        env["CONTENT_TYPE"] = req.headers.at("Content-Type");
    env["HTTP_REFERER"] = "";

    uri = req.uri;
    this->checkFile(uri);
    if (uri.find("?") != uri.npos) {
        query = uri.substr(uri.find("?") + 1);
        uri = uri.substr(0, uri.find("?"));
    }
    if (uri.find(cgiDir) != uri.npos) {
        script = uri.substr(uri.find(cgiDir) + cgiDir.size());
    }
    if (!script.size()){
        return nullptr;
    }
    env["SCRIPT_FILENAME"] = env["DOCUMENT_ROOT"] + cgiDir + script;
    if (stat(env["SCRIPT_FILENAME"].c_str(), &st) < 0) {
        // 404 not found
        return nullptr;
    }
    if (!(st.st_mode & S_IEXEC) != 0) {
        // error cannot exec
        return nullptr;
    }
    env["QUERY_STRING"] = query;
    env["SCRIPT_NAME"] = cgiDir + script;
    env["GATEWAY_INTERFACE"] = "CGI/1.1";
    env["REMOTE_ADDR"] = net.ip.str;
    env["REMOTE_PORT"] = std::to_string(net.port);
    env["REDIRECT_STATUS"] = "true";
    /*for (auto it: env){
        std::cout << it.first << " " << it.second << std::endl;
    }*/
    return mapToTab(env);
}

bool    Cgi::config(const zia::api::Conf& conf)
{}

bool    Cgi::handleSon(zia::api::HttpDuplex& http, int fd[2], const char **env)
{
    std::string bin("/usr/bin/php-cgi");
    char *argv[] = {
            strdup(bin.c_str()),
            NULL
    };
    for (int j = 0; env[j] != NULL; j++) {
        std::cout << env[j] << std::endl;
    }
    //close(http.info.sock->getSocket());
    close(fd[0]);
    dup2(fd[1], 1);
    return (execve(bin.c_str(), argv,  const_cast<char * const*>(env)));
}

void    Cgi::sendResponse(std::string raw)
{
    std::string header, body;
    size_t      index;

    index = raw.find(EOL EOL);
    header = raw.substr(0, index);
    if (index != std::string::npos){
        body = raw.substr(index + 4);
    }
    //std::cout << ">"<<raw << "<"<<std::endl;
    std::cout << "header:" << header << std::endl << std::endl << "BODY:" << body << std::endl;
}

bool    Cgi::handleFather(int fd[2], pid_t pid, zia::api::HttpDuplex& http)
{
    char buff[256];
    int cid;
    std::string body;
    int     size;

    close(fd[1]);
    waitpid(pid, &cid, 0);
    if (cid < 0) {
        close(fd[0]);
        return false;
    }
    size = read(fd[0], buff, 128);
    while (size != -1 && size) {
        body.append(buff, size);
        size = read(fd[0], buff, 128);
    }
    if (size == -1) {
        close(fd[0]);
        return false;
    }
    std::string tmp(body);
    this->sendResponse(tmp);
    //std::cout << body << std::endl;
    return true;
}

bool    Cgi::exec(zia::api::HttpDuplex& http)
{
    pid_t pid;
    int fd[2];
    const char **env;

    if ((env = createVirtualEnv(http.req, http.info)) == nullptr)
        return false;
    pipe(fd);
    pid = fork();
    if (pid == -1) {
        close(fd[0]);
        close(fd[1]);
        return false;
    }
    if (pid == 0) {
        return (this->handleSon(http, fd, env));
    } else {
        if (!this->handleFather(fd, pid, http))
            return false;
    }
    return true;
}

