#include "BusMessageHeader.hpp"


namespace messagebus
{
	MessageHeader::MessageHeader() : KvpDB("MessageHeader", ":", "\r\n")
	{
	}
	//This should really use header delegation but we don't have C++11 support.
	MessageHeader::MessageHeader(std::string headerBuffer) : KvpDB("MessageHeader", ":", "\r\n"), mHeaderBuffer(headerBuffer)
	{

	}
}
