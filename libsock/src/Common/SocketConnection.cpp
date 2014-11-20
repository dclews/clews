#include "SocketConnection.hpp"

//Only include unistd.h on non-windows platforms
//A bunch of network things also need defining on windows.
#if defined(__WIN32__) || defined(_WIN32)
typedef int socklen_t;
#define INET_ADDRSTRLEN (16)
#define INET6_ADDRSTRLEN (48)
#include <io.h> //close, read...
#include <WinSock2.h>
#include "../WIN/NetUtil.hpp"
#else
#include <unistd.h>
#endif

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
