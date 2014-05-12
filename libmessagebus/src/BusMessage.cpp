#include "BusMessage.hpp"
#include "BusMessageParseError.hpp"

using namespace std;

namespace messagebus
{
	Message::Message(std::string message)
	{
		string headerSizeField("HDR-SIZE:");
		if(!startsWith(message, headerSizeField))
		{
			throw MessageParseError("", "Failed to parse header. No size field present");
		}
		try
		{
			string sizeField = message.substr(headerSizeField.size(), message.find("\r\n"));
			sizeField
		}
		catch(const exception& e)
		{
			throw MessageParseError(e.what(), "Failed to parse header. Corrupt size field.");
		}

	}

	MessageHeader* Message::Header()
	{
		return mBusMessageHeader;
	}
}
