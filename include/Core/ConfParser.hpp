//
// Created by fumery on 02/02/18.
//

#ifndef CPP_ZIA_CONFPARSER_HPP
#define CPP_ZIA_CONFPARSER_HPP

#include	<string>
#include	<fstream>
#include <iostream>
#include <vector>
#include "api/conf.h"
#include "JsonObject.hpp"

class ConfParser {

public:
	ConfParser(const std::string);
	~ConfParser();
    bool Parse();
	std::string getArray(std::string obj);
	std::string getElem(std::string obj, std::string key);
	std::string extract(const std::string& str, const char *beg, const char *end, bool lof);

private:
    std::string FileName;
	std::string Content = "";
	zia::api::ConfObject ObjJson;
	zia::api::ConfArray ArrJson;
	std::vector<JsonObject> Object;
};


#endif //CPP_ZIA_CONFPARSER_HPP
