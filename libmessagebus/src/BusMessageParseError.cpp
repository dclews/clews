#include "BusMessageParseError.hpp"

namespace messagebus
{
	MessageParseError::MessageParseError(const char* friendlyDescription, std::string preciseError) : std::runtime_error(friendlyDescription), mPreciseError(preciseError)
	{
	}
	const std::string& MessageParseError::PreciseError()
	{
		return mPreciseError;
	}
}
