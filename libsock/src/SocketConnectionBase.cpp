#include "SocketConnectionBase.hpp"
#include <unistd.h>
#include <stdexcept>
#include <netinet/in.h>

using namespace std;

void SocketConnectionBase::sendHeader(size_t messageSize)
{
	mWrapMessages = false;
	write("!", 1);
	writeInt32(messageSize);
	write("$", 1);
	mWrapMessages = true;
}

size_t SocketConnectionBase::readHeader()
{
	mWrapMessages = false;
	char startMarker = readn(1, true).at(0);
	int32_t length = readInt32();
	char endMarker = readn(1, true).at(0);
	mWrapMessages = true;

	if(startMarker != '!' || endMarker != '$')
	{
		throw runtime_error("Improperly wrapped message.");
	}
	return length;
}

SocketConnectionBase::SocketConnectionBase(size_t bufferSize, bool wrapMessages) : mIsOpen(false), mBufferSize(bufferSize), mWrapMessages(wrapMessages) {}

vector<char> SocketConnectionBase::readn(uint32_t bufferSize, bool readUntilFull)
{
	vector<char> data(bufferSize);

	int n = ::read(mConnectionFD,data.data(),bufferSize);

	if (n < 0)
	{
		throw runtime_error("Failed to read from socket.");
	}
	if(readUntilFull)
	{
		while(n < bufferSize) //Read the remaining data;
		{
			n+= ::read(mConnectionFD, data.data(), bufferSize-n);
		}
	}

	data.resize(n);

	return data;
}
vector<char> SocketConnectionBase::read()
{
	if(mWrapMessages)
	{
		return readn(readHeader(), true);
	}
	else
	{
		return readn(mBufferSize);
	}
}

void SocketConnectionBase::write(const char* msg, size_t msgSize)
{
	if(mWrapMessages)
	{
		sendHeader(msgSize);
	}
	if(!mIsOpen)
	{
		throw runtime_error("Tried to write to a disconnected socket");
	}
	::write(mConnectionFD, msg, msgSize);
}
void SocketConnectionBase::write(const std::vector<char>& msg)
{
	if(mWrapMessages)
	{
		sendHeader(msg.size());
	}
	if(!mIsOpen)
	{
		throw runtime_error("Tried to write to a disconnected socket");
	}
	::write(mConnectionFD, msg.data(), msg.size());
}
void SocketConnectionBase::write(const std::string& msg)
{
	if(mWrapMessages)
	{
		sendHeader(msg.length());
	}
	if(!mIsOpen)
	{
		throw runtime_error("Tried to write to a disconnected socket");
	}
	::write(mConnectionFD, (const void*) msg.c_str(), msg.length()+1);
}

void SocketConnectionBase::operator<<(const vector<char>& msg)
{
	write(msg);
}
void SocketConnectionBase::operator<<(const string& msg)
{
	write(msg);
}

void SocketConnectionBase::writeInt32(int32_t msg)
{
	msg = htonl(msg);
	write((const char*) &msg, 4);
}

int32_t SocketConnectionBase::readInt32()
{
	if(mWrapMessages)
	{
		size_t messageSize = readHeader();
		if(messageSize != 4)
		{
			throw runtime_error("Message is too large to be an int32");
		}
	}
	vector<char> intVector = readn(4, true);
	int32_t* intPtr = (int32_t*) &intVector.at(0);

	return ntohl(*intPtr);
}

void SocketConnectionBase::setMessageWrapping(bool wrapMessages)
{
	mWrapMessages = wrapMessages;
}

bool SocketConnectionBase::messagesWrapped()
{
	return mWrapMessages;
}

bool SocketConnectionBase::SocketConnectionBase::isOpen()
{
	return mIsOpen;
}

void SocketConnectionBase::SocketConnectionBase::close()
{
	if(mIsOpen)	::close(mConnectionFD);
}

int SocketConnectionBase::FD()
{
	return mConnectionFD;
}
int SocketConnectionBase::bindToFD(int fd)
{
	return dup2(mConnectionFD, fd);
}
