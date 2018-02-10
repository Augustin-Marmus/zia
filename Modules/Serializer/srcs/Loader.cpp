//
// Created by Elias Demnati on 10/02/2018.
//

#include "Serializer.hpp"

#ifdef __unix__

extern "C" {
	zia::api::Module* create() {
		return (new Serializer);
	}
}

#endif // __unix__

#ifdef WIN32

extern "C" {
	__declspec(dllexport) zia::api::Serializer* __cdecl create() {
		return (new Serializer);
	}
}

#endif //WIN32