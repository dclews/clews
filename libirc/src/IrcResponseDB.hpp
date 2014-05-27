#ifndef IRC_RESPONSE_DB_HPP
#define IRC_RESPONSE_DB_HPP

#include <clews/core/CoreObject.hpp>
#include <clews/utility/FileUtil.hpp>
#include <clews/utility/StringUtil.hpp>
#include <clews/utility/KvpDB.hpp>

class IrcResponseDB : public KvpDB
{
public:
		IrcResponseDB();
		std::string ResponseString(int statusCode);
};

#endif
