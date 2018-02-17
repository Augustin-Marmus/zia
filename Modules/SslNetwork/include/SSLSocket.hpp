//
// Created by marmus_a on 29/01/18.
//

#ifndef CPP_ZIA_SOCKET_HPP
#define CPP_ZIA_SOCKET_HPP

#ifdef __unix__

#include "UnixSSLSocket.hpp"
using SSLSocket = UnixSSLSocket;

#endif
#ifdef _WIN32

#include "WinSSLSocket.hpp"
using SSLSocket = WinSSLSocket;

#endif

#endif //CPP_ZIA_SOCKET_HPP
