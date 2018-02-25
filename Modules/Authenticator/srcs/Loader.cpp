#include "Authenticator.hpp"

#ifdef __unix__

extern "C" {
	zia::api::Module* create() {
		return (new Authenticator);
	}
}

#endif // __unix__

#ifdef WIN32

extern "C" {
	__declspec(dllexport) zia::api::Module* __cdecl create() {
		return (new Authenticator);
	}
}

#endif //WIN32
