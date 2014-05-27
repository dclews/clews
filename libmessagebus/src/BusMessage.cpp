#include "BusMessage.hpp"
#include "BusMessageParseError.hpp"

using namespace std;

namespace messagebus
{
	Message::Message(std::string message) : mBody("MessageBody", ":", "\r\n")
	{
		string headerSizeField("HDR-SIZE:");
		if(!startsWith(message, headerSizeField))
		{
			throw MessageParseError("", "Failed to parse header. No size field present");
		}

		size_t headerSize = 0;
		try
		{
			string sizeField = message.substr(headerSizeField.size()+1, message.find("\r\n"));
			headerSize = stoi(sizeField);
		}
		catch(const exception& e)
		{
			throw MessageParseError(e.what(), "Failed to parse header. Corrupt size field.");
		}
		if(headerSize > message.size())
		{
			throw MessageParseError("", "Failed to parse header. Header size is larger than message.");
		}
		string header = message.substr(0, headerSize);
		mBusMessageHeader.Load(header);

		if(message.size() < header.size()+2 && message.substr(header.size(), 2) == "\r\n")
		{
			mBody.Load(message.substr(header.size()+2));
		}
	}

	MessageHeader& Message::Header()
	{
		return mBusMessageHeader;
	}
}
