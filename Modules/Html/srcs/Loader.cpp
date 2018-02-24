//
// Created by elias demnati on 29/01/18.
//

#include "Html.hpp"

#ifdef __unix__

extern "C" {
	zia::api::Module* create() {
		return (new Html);
	}
}

#endif // __unix__

#ifdef WIN32

extern "C" {
	__declspec(dllexport) zia::api::Module* __cdecl create() {
		return (new Html);
	}
}

#endif //WIN32
