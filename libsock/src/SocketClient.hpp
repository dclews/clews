#ifndef SOCKET_CLIENT_HPP
#define SOCKET_CLIENT_HPP

#include "SocketConnectionBase.hpp"

#include <string>
#include <string.h>

class SocketClient : public SocketConnectionBase
{
public:
    SocketClient(size_t bufferSize);
    bool Open(std::string hostname, uint32_t port);
};

#endif
