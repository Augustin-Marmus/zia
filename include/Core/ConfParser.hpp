//
// Created by fumery on 02/02/18.
//

#ifndef CPP_ZIA_CONFPARSER_HPP
#define CPP_ZIA_CONFPARSER_HPP

#include "api/conf.h"

class ConfParser {

public:
	ConfParser();
	~ConfParser();

private:
	zia::api::ConfObject ObjJson;
	zia::api::ConfArray ArrJson;
};


#endif //CPP_ZIA_CONFPARSER_HPP
