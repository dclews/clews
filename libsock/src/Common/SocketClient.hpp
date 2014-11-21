#ifndef SOCKET_CLIENT_HPP
#define SOCKET_CLIENT_HPP

#include "SocketConnectionBase.hpp"

#include <string>
#include <string.h>

class SocketClient : public SocketConnectionBase
{
public:
	SocketClient(size_t bufferSize=512);
	void open(std::string hostname, uint32_t port);
};

#endif
