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

const char **Cgi::createVirtualEnv(const zia::api::HttpRequest& req, const zia::api::NetInfo& net)
{
    std::map<std::string, std::string>  env;
    std::string query, uri, script, cgiDir;

    //TODO: find values in server's config
    env["DOCUMENT_ROOT"] = "/home/louis/tek3/cpp_zia";
    env["SERVER_NAME"] = "127.0.0.1";
    env["SERVER_PROTOCOL"] = "HTTP/1.1";
    env["SERVER_PORT"] = "80";
    env["SERVER_ADDR"] = "127.0.0.1";
    env["SERVER_SOFTWARE"] = "zia-redteam1.1";
    cgiDir = "/home/louis/tek3/cpp_zia";

    if (std::getenv("PATH")) {  env["PATH"] = std::getenv("PATH"); }
    if (std::getenv("HOME")) {  env["HOME"] = std::getenv("HOME"); }

    //TODO: find values in req
    env["REQUEST_METHOD"] = 1;
    env["REQUEST_URI"] = 1;
    env["HTTP_ACCEPT"] = 1;
    env["HTTP_ACCEPT_ENCODING"] = 1;
    env["HTTP_ACCEPT_LANGUAGE"] = 1;
    env["HTTP_CONNECTION"] = 1;
    env["HTTP_HOST"] = 1;
    env["HTTP_USER_AGENT"] = 1;
    env["HTTP_REFERER"] = 1;
    uri = "https://argos.sh/cgi-bin/phpInfo.php";

    if (uri.find("?") != uri.npos) {
        query = uri.substr(uri.find("?") + 1);
        uri = uri.substr(0, uri.find("?"));
    }
    if (uri.find("/cgi-bin/") != uri.npos) {
        script = uri.substr(uri.find("/cgi-bin/"));
    }
    env["QUERY_STRING"] = query;
    env["SCRIPT_NAME"] = script;
    env["SCRIPT_FILENAME"] = cgiDir + script;
    env["GATEWAY_INTERFACE"] = "CGI/1.1";
    env["REMOTE_ADDR"] = net.ip.str;
    //env["REMOTE_PORT"] = std::to_string(net.port);

    env["REDIRECT_STATUS"] = "200";

    return mapToTab(env);
}

bool    Cgi::config(const zia::api::Conf& conf)
{}

bool    Cgi::handleSon(zia::api::HttpDuplex& http, int fd[2])
{
    std::string bin("/usr/bin/php-cgi");
    char *argv[] = {
            strdup(bin.c_str()),
            NULL
    };
    const char **env = createVirtualEnv(http.req, http.info);
    for (int j = 0; env[j] != NULL; j++) {
        std::cout << env[j] << std::endl;
    }
    //close(http.info.sock->getSocket());
    close(fd[0]);
    dup2(fd[1], 1);
    return (execve(bin.c_str(), argv,  const_cast<char * const*>(env)));
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
    std::cout << body << std::endl;
    return true;
}

bool    Cgi::exec(zia::api::HttpDuplex& http)
{
    pid_t pid;
    int fd[2];

    pipe(fd);
    pid = fork();
    if (pid == -1) {
        close(fd[0]);
        close(fd[1]);
        return false;
    }
    if (pid == 0) {
        return (handleSon(http, fd));
    } else {
        if (!handleFather(fd, pid, http))
            return false;
    }
    return true;
}

