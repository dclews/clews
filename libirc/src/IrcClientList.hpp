#ifndef IRC_CLIENT_LIST_HPP
#define IRC_CLIENT_LIST_HPP

#include "IrcClient.hpp"
#include <vector>
#include <string>

class IrcClientList : public std::vector<IrcClient>
{
public:
	IrcClientList();
	IrcClient* ClientByIP(const std::string& ip);
	IrcClient* ClientByNick(const std::string& nick);
	IrcClient* ClientByUser(const std::string& user);
};
#endif
