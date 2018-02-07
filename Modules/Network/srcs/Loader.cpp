//
// Created by marmus_a on 29/01/18.
//

#include "Network.hpp"

#ifdef __unix__

extern "C" {
	zia::api::Net* getNetwork() {
		return (new Network);
	}
}

#endif // __unix__

#ifdef WIN32

extern "C" {
	__declspec(dllexport) zia::api::Net* __cdecl getNetwork() {
		return (new Network);
	}
}

#endif //WIN32