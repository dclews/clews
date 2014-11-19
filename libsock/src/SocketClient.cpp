#include "SocketClient.hpp"

#include <netinet/in.h>
#include <netdb.h>
#include <stdexcept>

using namespace std;

SocketClient::SocketClient(size_t bufferSize) : SocketConnectionBase(bufferSize)
{
}
void SocketClient::open(string hostname, uint32_t port)
{
	mConnectionFD = socket(AF_INET, SOCK_STREAM, 0);
	mForeignPort = port;

	if(mConnectionFD < 0)
	{
		throw runtime_error("Failed to open socket");
	}
	struct hostent* server = gethostbyname(hostname.c_str());

	if(server == NULL)
	{
		throw runtime_error("Failed to parse remote host name");
	}
	struct sockaddr_in serv_addr;
	memset((char*) &serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;

	memcpy((char*) &serv_addr.sin_addr.s_addr, (char*) server->h_addr, server->h_length);
	serv_addr.sin_port = htons(mForeignPort);

	if (connect(mConnectionFD,(struct sockaddr*) &serv_addr,sizeof(serv_addr)) < 0)
	{
		throw runtime_error("Failed to connect to host: " + hostname);
	}
	mIsOpen = true;
}
