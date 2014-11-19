#include "SocketConnection.hpp"
#include <unistd.h>
#include <stdexcept>

using namespace std;

SocketConnection::SocketConnection(int socketFD, size_t bufferSize) : SocketConnectionBase(bufferSize), mSocketFD(socketFD) {}

SocketConnection::~SocketConnection()
{
	close();
}
void SocketConnection::close()
{
	if(mIsOpen)	::close(mConnectionFD);
}
void SocketConnection::accept()
{
	struct sockaddr_in cli_addr;
	socklen_t clilen = sizeof(cli_addr);

	mConnectionFD = ::accept(mSocketFD, (struct sockaddr*) &cli_addr, &clilen);

	if(mConnectionFD<0)
	{
		throw runtime_error("Failed to accept connection.");
	}

	mIsOpen = true;
	mForeignIP = ntohl(cli_addr.sin_addr.s_addr);
	mForeignPort = ntohs((uint16_t) cli_addr.sin_port);

	char buffer[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &mForeignIP, buffer, INET_ADDRSTRLEN);
	mForeignIPStr = buffer;
}
