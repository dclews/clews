#ifndef IRC_CHANNEL_HPP
#define IRC_CHANNEL_HPP

#include "IrcClientList.hpp"
#include <string>

class IrcChannel
{
private:
	std::string mChannelName;
	IrcClientList mClients;
public:
	IrcChannel(const std::string& channelName);
	IrcClientList& Clients();
};

#endif
