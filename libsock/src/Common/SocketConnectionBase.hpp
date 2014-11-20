#ifndef SOCKET_CONNECTION_BASE_HPP
#define SOCKET_CONNECTION_BASE_HPP

#include <string>
#include <vector>
#include <stdint.h>

class SocketConnectionBase
{
protected:
	bool mIsOpen;
	int mConnectionFD;
	uint32_t mForeignIP;
	uint16_t mForeignPort;
	std::string mForeignIPStr;
	size_t mBufferSize;
	bool mWrapMessages;

	void sendHeader(size_t messageSize);
	size_t readHeader();
public:
	SocketConnectionBase(size_t bufferSize=512, bool wrapMessages=false);

	std::vector<char> readn(uint32_t bufferSize, bool readUntilFull=false);
	std::vector<char> read();

	void write(const char* msg, size_t msgSize);
	void write(const std::vector<char>& msg);
	void write(const std::string& msg);
	void operator<<(const std::vector<char>& msg);
	void operator<<(const std::string& msg);

	void writeInt32(int32_t msg);
	int32_t readInt32();

	void setMessageWrapping(bool wrapMessages);
	bool messagesWrapped();

	bool isOpen();
	void close();

	int FD();
	int bindToFD(int fd);
};

#endif
