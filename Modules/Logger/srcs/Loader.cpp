//
// Created by Pierre-Alexandre Monneau on 17/02/2018.
//

#include "Logger.hpp"

#ifdef __unix__

extern "C" {
	zia::api::Module* create() {
		return (new Logger);
	}
}

#endif // __unix__

#ifdef WIN32

extern "C" {
	__declspec(dllexport) zia::api::Module* __cdecl create() {
		return (new Logger);
	}
}

#endif //WIN32