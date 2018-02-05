//
// Created by fumery on 02/02/18.
//

#include "Core/ConfParser.hpp"

ConfParser::ConfParser(const std::string FileName) {
    this->FileName = FileName;

    std::string line;

    std::ifstream instream(FileName);
    if (instream)
    {
        while (getline(instream, line))
        {
            Content.append(line);
            Content.append("\n");
        }
    }
    //std::cout << Content << std::endl;
    instream.close();
}

ConfParser::~ConfParser() {
	
}

std::string ConfParser::extract(const std::string& str, const char *beg, const char *end, bool lof)
{
    std::size_t begPos;
    if ( (begPos = str.find(beg)) != std::string::npos )
    {
        std::size_t endPos ;
        if (lof) {
            if ((endPos = str.rfind(end)) != std::string::npos && endPos != begPos + 1)
                return str.substr(begPos + 1, endPos - begPos - 1);
        }
        else if ((endPos = str.find(end, begPos)) != std::string::npos && endPos != begPos+1 )
            return str.substr(begPos+1, endPos-begPos-1) ;
    }

    return std::string();
}

std::string ConfParser::getElem(std::string obj, std::string key)
{
    return extract(extract(obj, key.c_str(), ",", false), ":", "\"", true).erase(0,1);
}

std::string ConfParser::getArray(std::string obj)
{
    return extract(obj, "[", "]", true);
}

bool ConfParser::Parse()
{
    std::string arr = extract(Content, "[", "]", true);
    std::string tmp;
    JsonObject json;

    while (!(tmp = extract(arr, "{", "]}", false)).empty())
    {
        arr.erase(arr.find("{"), arr.find("]}"));
        tmp.append("]");

        std::cout << "name::" << getElem(tmp, "name")<< std::endl;
        std::cout << "filename::" << getElem(tmp, "moduleName")<< std::endl;
        std::cout << "moduleid::" << getElem(tmp, "id")<< std::endl;
        std::cout << "arr::" << getArray(tmp) << std::endl;

        json.setName(getElem(tmp, "name"));
        json.setModuleName(getElem(tmp, "moduleName"));
        json.setId(getElem(tmp, "moduleName"));

        Object.push_back(json);
    }

    for(auto i : Object) {
        std::cout << "-->" << i << "<--" << std::endl;
    }
}