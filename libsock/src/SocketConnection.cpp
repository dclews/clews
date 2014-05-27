#include "SocketConnection.hpp"

using namespace std;

SocketConnection::SocketConnection(int socketFD, size_t bufferSize) : SocketConnectionBase("SocketConnection", bufferSize), mSocketFD(socketFD) {}

SocketConnection::~SocketConnection()
{
		Close();
}
void SocketConnection::Close()
{
		if(mIsOpen)	close(mConnectionFD);
}
bool SocketConnection::Accept()
{
		SetPrintPrefix(__func__, FUNC_PRINT);

		struct sockaddr_in cli_addr;
		socklen_t clilen = sizeof(cli_addr);

		mConnectionFD = accept(mSocketFD, (struct sockaddr*) &cli_addr, &clilen);

		if(mConnectionFD>=0)
		{
				mIsOpen = true;
				mForeignIP = ntohl(cli_addr.sin_addr.s_addr);
				mForeignPort = ntohs((uint16_t) cli_addr.sin_port);

				char buffer[INET_ADDRSTRLEN];
				inet_ntop(AF_INET, &mForeignIP, buffer, INET_ADDRSTRLEN);
				mForeignIPStr = buffer;
		}
		else
		{
				ErrorOut() << "failed to accept connection." << endl;
		}
		ClearPrintPrefix();
		return mConnectionFD >= 0;
}
