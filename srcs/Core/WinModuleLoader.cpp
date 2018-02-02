//
// Created by marmus_a on 29/01/18.
//

#pragma once
#include "Core/WinModuleLoader.hpp"
#include "..\..\include\Core\WinModuleLoader.hpp"

WinModuleLoader::WinModuleLoader()
{
	this->handler = nullptr:
}

WinModuleLoader::~WinModuleLoader()
{
	if (this->handler) {
		//TODO close handler
	}
}

bool WinModuleLoader::loadLibrary(const std::string & path, const std::string & file)
{
	return false;
}

zia::api::Module * WinModuleLoader::loadModule(const std::string & moduleName)
{
	return nullptr;
}

zia::api::Net * WinModuleLoader::loadNetwork()
{
	return nullptr;
}

bool WinModuleLoader::unloadModule()
{
	return false;
}
