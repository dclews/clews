#include "HttpResponseDB.hpp"
#include <string.h>

using namespace std;

HttpResponseDB::HttpResponseDB() : KvpDB("HttpResponseDB", "\t") {}

std::string HttpResponseDB::ResponseString(int statusCode)
{
	char buffer[20];
	memset(buffer, 0, 20);
	snprintf(buffer, 20, "%d", statusCode);
	string response = Get(buffer);
	return response;
}
