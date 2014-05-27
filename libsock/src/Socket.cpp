#include "Socket.hpp"
#include <arpa/inet.h>

Socket::Socket(uint32_t portNumber, size_t bufferSize) : CoreObject("SocketStream"), mPortNumber(portNumber),
		mBufferSize(bufferSize), mIsOpen(false)
{
		DebugOut() << "PortNumber: " << mPortNumber << std::endl;
		mSocketFD = socket(AF_INET, SOCK_STREAM, 0);
}
Socket::~Socket()
{
		DebugOut() << "~SocketStream()" << std::endl;
}
bool Socket::Create()
{
	PushPrintPrefix(__func__, FUNC_PRINT);

	bool status = true;
	struct sockaddr_in serv_addr;

	StandardOut() << "Creating Socket on port " << mPortNumber << std::endl;

	mSocketFD = socket(AF_INET, SOCK_STREAM, 0);

	if (mSocketFD < 0)
	{
		 ErrorOut() << "Failed to create socket." << std::endl;
		 status = false;
	}
	else
	{
		memset((char*) &serv_addr, 0, sizeof(serv_addr));

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(mPortNumber);

		StandardOut() << "Binding to Socket " << mPortNumber << std::endl;

		if(bind(mSocketFD, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
		{
		 ErrorOut() << "Failed to bind to socket." << std::endl;
		 status = false;
		}
	}

	PopPrintPrefix();
	return status;
}

SocketConnection* Socket::Accept()
{
	SocketConnection* connection = new SocketConnection(mSocketFD, mBufferSize);
	if(connection->Accept())
	{
		mConnections.push_back(connection);
	}
	else
	{
		delete connection;
		connection = NULL;
	}
	return connection;
}
bool Socket::Destroy()
{
	PushPrintPrefix(__func__, FUNC_PRINT);
	ErrorOut() << "Destroying Socket." << std::endl;

	//CLEANUP SocketConnections here.
	for(size_t i=0;i<mConnections.size();++i)
	{
		SocketConnection* con = mConnections[i];
		con->Close();
		delete con;
	}
	mConnections.clear();

	PopPrintPrefix();
	return true;
}
int Socket::Listen()
{
	PushPrintPrefix(__func__, FUNC_PRINT);
	StandardOut() << "Listening for connections..." << std::endl;
	listen(mSocketFD,5);
	PopPrintPrefix();
	return 0;
}
