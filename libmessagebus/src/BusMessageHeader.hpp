#ifndef BUS_MESSAGE_HEADER_HPP
#define BUS_MESSAGE_HEADER_HPP

#include <string>

#include <clews/utility/KvpDB.hpp>

namespace messagebus
{
	class MessageHeader : public KvpDB
	{
	private:
		std::string mHeaderBuffer;
	public:
		MessageHeader();
		MessageHeader(std::string headerBuffer);
	};
}

#endif
