#ifndef SOCKET_CONNECTION_BASE_HPP
#define SOCKET_CONNECTION_BASE_HPP

#include <clews/core/CoreObject.hpp>
#include <string>
#include <vector>

class SocketConnectionBase
{
protected:
	bool mIsOpen;
	int mConnectionFD;
	uint32_t mForeignIP;
	uint16_t mForeignPort;
	std::string mForeignIPStr;
	size_t mBufferSize;
public:
	SocketConnectionBase(size_t bufferSize);

	std::vector<char> readn(uint32_t bufferSize);
	std::vector<char> read();

	void write(const char* msg, size_t msgSize);
	void write(const std::vector<char>& msg);
	void write(const std::string& msg);
	void operator<<(const std::vector<char>& msg);
	void operator<<(const std::string& msg);

	bool isOpen();
	void close();

	int FD();
	int bindToFD(int fd);
};

#endif
