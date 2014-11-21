#include "Socket.hpp"

//Only include netdb.h and arpa/inet.h on non-windows platforms.
#if defined(__WIN32__) || defined(_WIN32)
#include <WinSock2.h>
#else
#include <arpa/inet.h>
#endif

#include <stdexcept>

using namespace std;

Socket::Socket(uint32_t portNumber, size_t bufferSize) : mPortNumber(portNumber),
		mBufferSize(bufferSize), mIsOpen(false)
{
		mSocketFD = socket(AF_INET, SOCK_STREAM, 0);
}
Socket::~Socket()
{
}
void Socket::create()
{
	struct sockaddr_in serv_addr;

	mSocketFD = socket(AF_INET, SOCK_STREAM, 0);

	if (mSocketFD < 0)
	{
		 throw runtime_error("Failed to create socket.");
	}
	memset((char*) &serv_addr, 0, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(mPortNumber);


	if (bind(mSocketFD, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		throw runtime_error("Failed to bind to socket.");
	}
}

SocketConnection* Socket::accept()
{
	SocketConnection* connection = new SocketConnection(mSocketFD, mBufferSize);

	try
	{
		connection->accept();
		mConnections.push_back(connection);
	}
	catch(const runtime_error& re)
	{
		delete connection;
		throw runtime_error("Failed to accept  connection");
	}
	return connection;
}
void Socket::destroy()
{
	for(size_t i=0;i<mConnections.size();++i)
	{
		SocketConnection* con = mConnections[i];
		con->close();
		delete con;
	}
	mConnections.clear();
}
void Socket::listen()
{
	::listen(mSocketFD,5);
}
