#ifndef SOCKETCONNECTION_HPP
#define SOCKETCONNECTION_HPP

//Only include netdb.h and arpa/inet.h on non-windows platforms.
#if defined(__WIN32__) || defined(_WIN32)
#include <WinSock2.h>
#else
#include <netdb.h>
#include <arpa/inet.h>
#endif

#include <string>
#include <string.h>
#include "SocketConnectionBase.hpp"

class SocketConnection : public SocketConnectionBase
{
private:
	int mSocketFD;

public:
	SocketConnection(int socketFD, size_t bufferSize=512);
	~SocketConnection();

	void close();
	void accept();
};

#endif // SOCKETCONNECTION_HPP
