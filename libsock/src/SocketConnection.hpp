#ifndef SOCKETCONNECTION_HPP
#define SOCKETCONNECTION_HPP

#include <string>
#include <string.h>
#include <netdb.h>
#include "SocketConnectionBase.hpp"
#include <arpa/inet.h>

class SocketConnection : public SocketConnectionBase
{
private:
	int mSocketFD;

public:
	SocketConnection(int socketFD, size_t bufferSize);
	~SocketConnection();

	bool open(std::string hostname);
	void close();
	void accept();
};

#endif // SOCKETCONNECTION_HPP
