#ifndef BUS_MESSAGE_PARSE_ERROR_HPP
#define BUS_MESSAGE_PARSE_ERROR_HPP

#include <stdexcept>
#include <string>

namespace messagebus
{
	class MessageParseError : public std::runtime_error
	{
	private:
		std::string mPreciseError;
	public:
		MessageParseError(const char* friendlyDescription, const std::string preciseError);
		const std::string& PreciseError();
		~MessageParseError() throw();
	};
}

#endif
