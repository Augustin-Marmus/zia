//
// Created by Elias Demnati on 16/02/2018.
//

#include    <sstream>
#include    <iostream>
#include    "Html.hpp"

bool        Html::config(const zia::api::Conf& conf) {
  const std::string *dir;

  if (!(dir = std::get_if<std::string>(&conf.at("public").v))) {
    std::cerr << "Error: Missing dir field in HTML configuration" << std::endl;
    return (false);
  }
    std::cout << *dir << std::endl;
  this->htmlFolderPath = *dir;
  return true;
}

bool        Html::checkUriAndRequest(zia::api::HttpDuplex& html, std::ifstream& fileStream) {
  if (html.req.method != zia::api::http::Method::get){

      return false;
  }
  fileStream.open(this->htmlFolderPath + html.req.uri, std::ifstream::in);

  for (auto it : map){
      if (html.req.uri.substr(html.req.uri.find_last_of(".") + 1) == map.first){
          html.resp.headers["Content-Type"] = map.second;
      }
  }

  if (!fileStream) {
      std::string body("<html><head>\n<title>404 Not Found</title>\n</head><body>\n<h1>Not Found</h1>\n<p>The requested URL " + html.req.uri + " was not found on this server.</p>\n</body></html>\r\n");
      html.resp.headers["Content-Type"] = "text/html; charset=UTF-8";
      html.resp.version = zia::api::http::Version::http_1_1;
      html.resp.status = zia::api::http::common_status::not_found;
      html.resp.headers["Content-Length"] = std::to_string(body.length());
      html.resp.headers["status"] = "404";
      html.resp.body.clear();
      for (auto c : body) {
          html.resp.body.push_back(static_cast<std::byte>(c));
      }
      return false;
  }

  return true;
}

bool        Html::getFile(zia::api::HttpDuplex& html, std::ifstream& fileStream) {
  std::string       fileStr;
  std::stringstream stream;

  stream << fileStream.rdbuf();
  fileStr = stream.str();
  for (auto& it: fileStr) {
    if (it == '\n')
      html.resp.body.push_back(static_cast<std::byte>('\r'));
    html.resp.body.push_back(static_cast<std::byte>(it));
  }

  html.resp.version = zia::api::http::Version::http_1_1;
  html.resp.status = zia::api::http::common_status::ok;
  html.resp.headers["Content-Length"] = std::to_string(html.resp.body.size());
  return true;
}

bool        Html::exec(zia::api::HttpDuplex& html) {
  std::ifstream fileStream;
  return this->checkUriAndRequest(html, fileStream) && this->getFile(html, fileStream);
}
