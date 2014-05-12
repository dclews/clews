#ifndef BUS_MESSAGE_HEADER_HPP
#define BUS_MESSAGE_HEADER_HPP

#include <string>

namespace messagebus
{
	class MessageHeader
	{
	private:
		std::string& mHeaderBuffer;
	public:
		MessageHeader(std::string& headerBuffer);
		const std::string& Field(std::string headerField);
		int IntField(std::string headerField);
	};
}

#endif
