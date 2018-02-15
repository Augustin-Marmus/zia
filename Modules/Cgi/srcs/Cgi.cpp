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
    std::string query, uri, script, cgiDir, cgiRealDir;
    struct stat  st;


    //TODO: find values in server's config
    env["DOCUMENT_ROOT"] = _conf["DOCUMENT_ROOT"];
    env["SERVER_NAME"] = _conf["SERVER_IP"];
    env["SERVER_PROTOCOL"] = "HTTP/1.1";
    env["SERVER_PORT"] = _conf["SERVER_PORT"];
    env["SERVER_ADDR"] = _conf["SERVER_IP"];
    env["SERVER_SOFTWARE"] = _conf["SERVER_SOFTWARE"];
    cgiDir = _conf["CGI_ALIAS"];

    if (std::getenv("PATH")) {  env["PATH"] = std::getenv("PATH"); }
    if (std::getenv("HOME")) {  env["HOME"] = std::getenv("HOME"); }

    //TODO: find values in req
    env["REQUEST_METHOD"] = "post";
    //env["REQUEST_URI"] = req.uri;
    //uri = req.uri;
    env["REQUEST_URI"] = "http://localhost:1337/cgi-bin/env.php";
    uri = "http://localhost:1337/cgi-bin/env.php";
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
    std::cout <<env["SCRIPT_FILENAME"] << std::endl;

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

const std::string     *Cgi::getValueByKey(const std::string& key, const zia::api::Conf& conf){
    const std::string *value;
    if (!(value = std::get_if<std::string>(&conf.at(key).v))) {
        std::cerr << "Error: Missing field name in a Module" << std::endl;
        return (nullptr);
    }
    std::cout << *value << std::endl;
    return (value);
}

bool    Cgi::config(const zia::api::Conf& conf) {

    _conf["PHP_CGI"] = ((getValueByKey("php-cgi", conf) != nullptr) ? *getValueByKey("php-cgi", conf) : std::to_string(MAGICK));
    _conf["DOCUMENT_ROOT"] = ((getValueByKey("document_root", conf) != nullptr) ? *getValueByKey("document_root", conf) : std::to_string(MAGICK));
    _conf["SERVER_PORT"] = ((getValueByKey("port", conf) != nullptr) ? *getValueByKey("port", conf) : std::to_string(MAGICK));
    _conf["SERVER_IP"] = ((getValueByKey("ip", conf) != nullptr) ? *getValueByKey("ip", conf) : std::to_string(MAGICK));
    _conf["CGI_ALIAS"] = ((getValueByKey("cgi_alias", conf) != nullptr) ? *getValueByKey("cgi_alias", conf) : std::to_string(MAGICK));
    _conf["SERVER_SOFTWARE"] = ((getValueByKey("server_software", conf) != nullptr) ? *getValueByKey("server_software", conf) : std::to_string(MAGICK));
    for (auto it : _conf)
        if (it.second == std::to_string(MAGICK))
            return false;
    return (true);
}

bool    Cgi::handleSon(zia::api::HttpDuplex& http, int fd[2], const char **env)
{
    std::string bin(_conf["PHP_CGI"]);
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

void    Cgi::sendResponse(std::string raw, zia::api::HttpDuplex& http)
{
    std::string header, body;
    size_t      index;

    index = raw.find(EOL EOL);
    header = raw.substr(0, index);
    if (index != std::string::npos){
        body = raw.substr(index + 4);
    }
    raw.insert(0, "HTTP1/1 200 OK\r\nContent-Length:" + std::to_string(body.length()) + "\r\n");
    zia::api::Net::Raw res;
    for (auto c : raw) {
        res.push_back(static_cast<std::byte>(c));
    }
    http.raw_resp.clear();
    http.raw_resp = res;
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
    this->sendResponse(tmp, http);
    //std::cout << body << std::endl;
    return true;
}

bool    Cgi::exec(zia::api::HttpDuplex& http)
{
    pid_t pid;
    int fd[2];
    const char **env;
    std::cout << "EXEC Cgi" << std::endl;
    if ((env = createVirtualEnv(http.req, http.info)) == nullptr){
        std::cout << "Cgi: ENV is NULL" << std::endl;
        return false;
    }
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

