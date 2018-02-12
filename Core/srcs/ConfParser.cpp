//
// Created by fumery on 02/02/18.
//

#include "ConfParser.hpp"

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
    instream.close();
}

ConfParser::~ConfParser() {
	
}

std::string ConfParser::getKey(std::string elem)
{
	std::string key;

	key = elem.insert(0, "\"");
	key = utils.extract(key, "\"", ":");
	std::cout << "-->" << key << "<--" << std::endl;
	key.erase(key.find("\""), key.find("\"")+1);
	key.erase(key.find("\""), key.find("\"")+1);
	return key;
}

std::pair<std::string, zia::api::ConfValue> ConfParser::getPair(std::string elem)
{
	std::pair<std::string, zia::api::ConfValue> elemConf;
	std::string key;
	std::string value;

	key = getKey(elem);
	std::cout << "-->" << key << "<--" << std::endl;
	elemConf.first = key;
	value = elem;
	value.erase(0, elem.find(":"));
	elem = utils.extract(value, "\"", "\"");
	if (elem.compare("") == 0)
		elem = value.erase(0, 1);
	if (elem.find('\"') != elem.npos)
		elem.erase(elem.find('\"'));
	std::cout << elem << std::endl;
	elemConf.second.v = elem;
	return elemConf;
}

zia::api::ConfArray ConfParser::toConfArray(std::string All)
{
	zia::api::ConfArray Array;
	zia::api::ConfObject ConfObj;
	zia::api::ConfValue ConfValue;
	std::string tmp;

	All.erase(0, 1);
	All.erase(All.length()-1);
	while (!All.empty()) {
		tmp = All.substr(All.find("{"), utils.getEnd(All, "{", "}"));
		All.erase(All.find(tmp), All.find(tmp)+tmp.length());
		tmp.erase(0, 1);
		tmp.erase(tmp.length()-1);
		ConfObj = toConfObj(tmp);
		ConfValue.v = ConfObj;
		Array.push_back(ConfValue);
		if (All[0] == ',')
			All.erase(0, 1);
	}
	return Array;
}

zia::api::ConfObject ConfParser::toConfObj(std::string All)
{
	std::string tmp;
	std::string key;
	zia::api::ConfObject res;
	std::pair<std::string,zia::api::ConfValue> elem;

	while (utils.extract(All, "\"", "\0").compare("") != 0)
	{
		if (utils.CheckStr(All)) {
			tmp = utils.extract(All, "\"", ",");
			if (tmp.compare("") == 0)
				tmp = utils.extract(All, "\"", "\0");
			tmp.insert(0, "\"");
			All.erase(All.find(tmp), All.find(tmp)+tmp.length());
			if (All[0] == ',')
				All.erase(0, 1);
			elem = getPair(tmp);
		}
		else if (utils.extract(All, "\"", ",").find("[") != All.npos)
		{
			key = All.substr(All.find("\""), All.find(":")+1);
			tmp = utils.getFragment(All, "[", "]");
			elem.first = key;
			elem.second.v = toConfArray(tmp);
			All.erase(All.find(key), All.find(key)+key.length());
			All.erase(All.find(tmp), All.find(tmp)+tmp.length());
		}
		else {
			key = All.substr(All.find("\""), All.find(":")+1);
			tmp = utils.getFragment(All, "{", "}").erase(0, 1).erase(utils.getFragment(All, "{", "}").length()-1);
			All.erase(All.find(key), All.find(key)+key.length());
			All.erase(All.find(tmp), All.find(tmp)+tmp.length());
			if (All[1] == ',' && All[0] == '{')
				All.erase(0, 2);
			else if (All[0] == '{')
				All.erase(0, 1);
			elem.first = key;
			elem.second.v = toConfObj(tmp);
		}
		res.insert(elem);
	}
	return res;
}

std::pair<std::string, zia::api::ConfValue> ConfParser::ParseFirstBloc()
{
	std::string key;
	std::string Frame;
	std::pair<std::string, zia::api::ConfValue> elem;

	zia::api::ConfObject test;

	if (Content.find("{") < Content.find("[")) {
		Frame = utils.getFragment(Content, "{", "}");
		key = utils.extract(Content, "\"", ":");
		key.erase(key.find("\""));
		elem.first = key;
		Content.erase(Content.find("{"), utils.getEnd(Content, "{", "}") - Content.find("{"));
		Content.erase(Content.find("\""), Content.find(":") - 1);
		Frame.erase(0, 1);
		Frame = Frame.erase(Frame.length() - 1, Frame.length());
		std::cout << "FRAME-->" << Frame << std::endl;
		elem.second.v = toConfObj(utils.ClearIt(Frame));

		/////////////////////////////////////////////////////////////////////////////////////////////
		test = std::get<zia::api::ConfObject>(elem.second.v);
		std::string ole = std::get<std::string>(test.at("titi").v);
		std::cout << ole << std::endl;
		/////////////////////////////////////////////////////////////////////////////////////////////

	} else {
		Frame = utils.getFragment(Content, "[", "]");
		key = utils.extract(Content, "\"", ":");
		key.erase(key.find("\""));
		elem.first = key;
		Content.erase(Content.find("\""), Content.find(":") - 1);
		Content.insert(0, "[");
		Content.erase(Content.find("["), utils.getEnd(Content, "[", "]"));
		std::cout << "FRAME-->" << Frame << std::endl;
		elem.second.v = toConfArray(utils.ClearIt(Frame));
	}
	return elem;
}

zia::api::ConfObject *ConfParser::Parse()
{
	zia::api::ConfObject *All = new zia::api::ConfObject();

	Content.erase(0,1);
	Content.erase(Content.length()-2);

	try {
		while (Content.find("{") != Content.npos) {
			All->insert(ParseFirstBloc());
		}
	} catch (const std::out_of_range& err)
	{
		std::cerr << "Ah! Out of Range error: " << err.what() << '\n';
	}

	return All;
}
