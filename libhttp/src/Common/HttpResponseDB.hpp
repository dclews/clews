#ifndef HTTP_RESPONSE_DB_HPP
#define HTTP_RESPONSE_DB_HPP

#include <clews/core/CoreObject.hpp>
#include <clews/utility/FileUtil.hpp>
#include <clews/utility/StringUtil.hpp>
#include <clews/utility/KvpDB.hpp>

class HttpResponseDB : public KvpDB
{
public:
	HttpResponseDB();
	std::string ResponseString(int statusCode);
};

#endif
