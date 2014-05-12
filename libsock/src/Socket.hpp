#ifndef SOCKET_STREAM_H
#define SOCKET_STREAM_H

#if defined(__sun) && defined(__SVR4)
typedef long id_t;
typedef id_t ctid_t;
typedef id_t zoneid_t;
#endif

#include <fcntl.h>
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

#include <sys/types.h>
#include <sys/socket.h>

#include "SocketConnection.hpp"
#include "SocketClient.hpp"
#include <clews/core/CoreObject.hpp>

class Socket : public CoreObject
{
private:
	int mSocketFD;
	uint32_t mPortNumber;
	size_t mBufferSize;
	bool mIsOpen;
	std::vector<SocketConnection*> mConnections;
public:
	Socket(uint32_t portNumber, size_t bufferSize);
	~Socket();

	SocketConnection* Open(std::string hostname);

	bool Create();
	bool Destroy();

	int Listen();
	SocketConnection* Accept();
};

#endif
