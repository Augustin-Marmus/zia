//
// Created by fumery on 02/02/18.
//

#include "Core/JsonObject.hpp"

JsonObject::JsonObject()
{

}

JsonObject::JsonObject(std::string _name, std::string _moduleName, std::string _id):
        name(_name), moduleName(_moduleName), id(_id)

{

}

JsonObject::~JsonObject()
{

}

void JsonObject::setName(std::string name)
{
    this->name = name;
}

void JsonObject::setModuleName(std::string moduleName)
{
    this->moduleName = moduleName;
}

void JsonObject::setId(std::string id)
{
    this->id = id;
}

std::string JsonObject::getName() const
{
    return this->name;
}

std::string JsonObject::getModuleName() const
{
    return this->moduleName;
}

std::string JsonObject::getId() const
{
    return this->id;
}

std::ostream& operator<<(std::ostream& os, JsonObject const &obj)
{
    os << obj.getName() << " " << obj.getModuleName() << " " << obj.getId();
    return os;
}