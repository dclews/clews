#ifndef SOCKET_CONNECTION_BASE_HPP
#define SOCKET_CONNECTION_BASE_HPP

#include <clews/core/CoreObject.hpp>
#include <string>
#include <mutex>

class SocketConnectionBase : public CoreObject
{
protected:
		bool mIsOpen;
		int mConnectionFD;
		uint32_t mForeignIP;
		uint16_t mForeignPort;
		std::string mForeignIPStr;
		size_t mBufferSize;
		std::mutex mtx;
public:
		SocketConnectionBase(std::string typeID, size_t bufferSize);

		std::string Readn(uint32_t bufferSize);
		std::string Read();
		void operator>>(std::string& msg);

		void Write(const std::string& msg);
		void WriteLine(const std::string& msg);
		void operator<<(std::string msg);

		bool IsOpen();
		void Close();

		int FD();
		int BindToFD(int fd);
		std::string ForeignIP();
};

#endif
