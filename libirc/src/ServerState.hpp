#ifndef IRC_SERVER_STATE_HPP
#define IRC_SERVER_STATE_HPP

#include "IrcClientList.hpp"
#include "IrcChannel.hpp"
#include <map>

class IrcServerState
{
private:
	IrcClientList mClients;
	std::map<std::string, IrcChannel> mChannels;
public:
	IrcServerState();
	IrcClientList& Clients();
	std::map<std::string, IrcChannel>& Channels();
};

#endif
