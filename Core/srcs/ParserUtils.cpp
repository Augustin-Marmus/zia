//
// Created by fumery on 02/02/18.
//

#include "ParserUtils.hpp"

ParserUtils::ParserUtils() {
}

ParserUtils::~ParserUtils() {
	
}

std::string ParserUtils::extract(const std::string& str, const char *beg, const char *end)
{
    std::size_t begPos;
    if ( (begPos = str.find(beg)) != std::string::npos )
    {
        std::size_t endPos ;
		if ((endPos = str.find(end, begPos)) != std::string::npos && endPos != begPos+1 )
            return str.substr(begPos+1, endPos-begPos-1) ;
    }

    return std::string();
}

std::string ParserUtils::getFragment(std::string all, std::string begin, std::string end)
{
	all.erase(0, 1);
	int cmp = 0;
	int c = all.find(begin);
	std::string Frag;
	bool finder = false;
	std::string tmp;

	while (!finder)
	{
		if (all[c] && all[c] == end[0])
			cmp--;
		else if (all[c] && all[c] == begin[0])
			cmp++;
		if (cmp == 0)
		{
			Frag.push_back(all[c]);
			return Frag;
		}
		if (all[c+1] == '\0')
			return Frag;
		Frag.push_back(all[c]);
		c++;
	}
	return Frag;
}

int ParserUtils::getEnd(std::string all, std::string begin, std::string end)
{
	int cmp = 0;
	int c = all.find(begin);
	bool finder = false;

	while (!finder)
	{
		if (all[c] == end[0])
			cmp--;
		else if (all[c] == begin[0])
			cmp++;
		if (cmp == 0)
			return ++c;
		if (all[c+1] == '\0')
			return c;
		c++;
	}
	return c;
}

bool ParserUtils::CheckStr(std::string All)
{
	if (extract(All, "\"", "\0").find(",") == All.npos && extract(All, "\"", "\0").find("{") != All.npos && extract(All, "\"", "\0").find("[") != All.npos) {
		return false;
	}
	else if (All[All.find(":")+1] == '{')
		return false;
	return (extract(All, "\"", ",").find("{") == All.npos &&
			extract(All, "\"", ",").find("[") == All.npos);
}

template<typename T, typename P>
T ParserUtils::rmSpc(T start, T end, P p)
{
	T toRet = start;
	for (T cmp = start; cmp != end ; ++cmp) {
		if (!p(*cmp))
			*(toRet++) = *cmp;
	}
	return toRet;
}

std::string ParserUtils::ClearIt(std::string str)
{
	str.erase(rmSpc(str.begin(), str.end(), isspace), str.end());
	return str;
}

bool ParserUtils::CheckFile(std::string All)
{
	All = ClearIt(All);

	if (All[0] != '{' || All[All.length()-1] != '}')
		return false;
	return true;
}