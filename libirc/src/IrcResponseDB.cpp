#include "IrcResponseDB.hpp"
#include <string.h>

using namespace std;

IrcResponseDB::IrcResponseDB() : KvpDB("IrcResponseDB", "\t") {}

std::string IrcResponseDB::ResponseString(int statusCode)
{
		char buffer[20];
		memset(buffer, 0, 20);
		snprintf(buffer, 20, "%d", statusCode);
		string response = Get(buffer);
		return response;
}
