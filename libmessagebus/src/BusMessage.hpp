#ifndef BUS_MESSAGE_HPP
#define BUS_MESSAGE_HPP

#include <string>
#include <clews/utility/KvpDB.hpp>
#include "BusMessageHeader.hpp"

namespace messagebus
{
	class Message
	{
	private:
		KvpDB mBody;
		MessageHeader mBusMessageHeader;
	public:
		Message(std::string header, std::string body);
		Message(std::string message);
		MessageHeader& Header();
		KvpDB& Body();
	};
}

#endif


