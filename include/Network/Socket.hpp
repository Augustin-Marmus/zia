//
// Created by marmus_a on 29/01/18.
//

#ifndef CPP_ZIA_SOCKET_HPP
#define CPP_ZIA_SOCKET_HPP

#ifdef __unix__

#include <Network/UnixSocket.hpp>
using Socket = UnixSocket;

#endif
#ifdef _WIN32

#include <Network/WinSocket.hpp>
using Socket = WinSocket;

#endif

#endif //CPP_ZIA_SOCKET_HPP
