//
// Created by fumery on 02/02/18.
//

#ifndef CPP_ZIA_JSONOBJECT_HPP
#define CPP_ZIA_JSONOBJECT_HPP

#include <iostream>
#include <string>

class JsonObject
{
public:
    JsonObject();
    JsonObject(std::string, std::string, std::string);
    ~JsonObject();

    void setName(std::string);
    void setModuleName(std::string);
    void setId(std::string);
    std::string getName() const;
    std::string getModuleName() const;
    std::string getId() const;
private:
    std::string name;
    std::string moduleName;
    std::string id;
};

std::ostream& operator<<(std::ostream& os, JsonObject const &obj);

#endif //CPP_ZIA_JSONOBJECT_HPP
