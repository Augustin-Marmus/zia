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
  std::unordered_map<std::string, std::string> MimeType = {
        {"txt", "text/plain"},
        {"csv", "text/csv"},
        {"htm", "text/html"},
        {"html", "text/html"},
        {"php", "text/html"},
        {"css", "text/css"},
        {"js", "application/javascript"},
        {"json", "application/json"},
        {"xml", "application/xml"},
        {"swf", "application/x-shockwave-flash"},
        {"flv", "video/x-flv"},
        // Images
        {"png", "image/png"},
        {"jpe", "image/jpeg"},
        {"jpeg", "image/jpeg"},
        {"jpg", "image/jpeg"},
        {"gif", "image/gif"},
        {"bmp", "image/bmp"},
        {"ico", "image/vnd.microsoft.icon"},
        {"tiff", "image/tiff"},
        {"tif", "image/tiff"},
        {"svg", "image/svg+xml"},
        {"svgz", "image/svg+xml"},
        // Archives
        {"zip", "application/zip"},
        {"rar", "application/x-rar-compressed"},
        {"exe", "application/x-msdownload"},
        {"msi", "application/x-msdownload"},
        {"cab", "application/vnd.ms-cab-compressed"},
        // Audio/video
        {"mpg", "audio/mpeg"},
        {"mp2", "audio/mpeg"},
        {"mp3", "audio/mpeg"},
        {"mp4", "audio/mp4"},
        {"qt", "video/quicktime"},
        {"mov", "video/quicktime"},
        {"ogg", "audio/ogg"},
        {"oga", "audio/ogg"},
        {"wav", "audio/wav"},
        {"webm", "audio/webm"},
        {"aac", "audio/aac"},
        // Adobe
        {"pdf", "application/pdf"},
        {"psd", "image/vnd.adobe.photoshop"},
        {"ai", "application/postscript"},
        {"eps", "application/postscript"},
        {"ps", "application/postscript"},
        // MS Office
        {"doc", "application/msword"},
        {"dot", "application/msword"},
        {"docx", "application/vnd.openxmlformats-officedocument.wordprocessingml.document"},
        {"dotx", "application/vnd.openxmlformats-officedocument.wordprocessingml.template"},
        {"docm", "application/vnd.ms-word.document.macroEnabled.12"},
        {"dotm", "application/vnd.ms-word.template.macroEnabled.12"},
        {"odt", "application/vnd.oasis.opendocument.text"},
        {"rtf", "application/rtf"},
        {"xls", "application/vnd.ms-excel"},
        {"xlt", "application/vnd.ms-excel"},
        {"xla", "application/vnd.ms-excel"},
        {"xlsx", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"},
        {"xltx", "application/vnd.openxmlformats-officedocument.spreadsheetml.template"},
        {"xlsm", "application/vnd.ms-excel.sheet.macroEnabled.12"},
        {"xltm", "application/vnd.ms-excel.template.macroEnabled.12"},
        {"xlam", "application/vnd.ms-excel.addin.macroEnabled.12"},
        {"xlsb", "application/vnd.ms-excel.sheet.binary.macroEnabled.12"},
        {"ppt", "application/vnd.ms-powerpoint"},
        {"pot", "application/vnd.ms-powerpoint"},
        {"pps", "application/vnd.ms-powerpoint"},
        {"ppa", "application/vnd.ms-powerpoint"},
        {"pptx", "application/vnd.openxmlformats-officedocument.presentationml.presentation"},
        {"potx", "application/vnd.openxmlformats-officedocument.presentationml.template"},
        {"ppsx", "application/vnd.openxmlformats-officedocument.presentationml.slideshow"},
        {"ppam", "application/vnd.ms-powerpoint.addin.macroEnabled.12"},
        {"pptm", "application/vnd.ms-powerpoint.presentation.macroEnabled.12"},
        {"potm", "application/vnd.ms-powerpoint.template.macroEnabled.12"},
        {"ppsm", "application/vnd.ms-powerpoint.slideshow.macroEnabled.12"},
        {"mdb", "application/vnd.ms-access"},
        {"ods", "application/vnd.oasis.opendocument.spreadsheet"}
  };
};

#endif              //CPP_ZIA_HTML_HPP
