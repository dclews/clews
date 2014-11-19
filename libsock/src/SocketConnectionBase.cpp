#include "SocketConnectionBase.hpp"
#include <unistd.h>
#include <stdexcept>

using namespace std;

SocketConnectionBase::SocketConnectionBase(size_t bufferSize) : mIsOpen(false), mBufferSize(bufferSize) {}

vector<char> SocketConnectionBase::readn(uint32_t bufferSize)
{
	vector<char> data(bufferSize);

	int n = ::read(mConnectionFD,data.data(),bufferSize);

	if (n < 0)
	{
		throw runtime_error("Failed to read from socket.");
	}

	data.resize(n);

	return data;
}
vector<char> SocketConnectionBase::read()
{
	return readn(mBufferSize);
}

void SocketConnectionBase::write(const char* msg, size_t msgSize)
{
	::write(mConnectionFD, msg, msgSize);
}
void SocketConnectionBase::write(const std::vector<char>& msg)
{
	::write(mConnectionFD, msg.data(), msg.size());
}
void SocketConnectionBase::write(const std::string& msg)
{
	::write(mConnectionFD, (const void*) msg.c_str(), msg.length());
}

void SocketConnectionBase::operator<<(const vector<char>& msg)
{
	write(msg);
}
void SocketConnectionBase::operator<<(const string& msg)
{
	write(msg);
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
