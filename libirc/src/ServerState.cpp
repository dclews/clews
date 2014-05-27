#include "ServerState.hpp"

IrcServerState::IrcServerState(){}
IrcClientList& IrcServerState::Clients() {return mClients;}

std::map<std::string, IrcChannel>&IrcServerState::Channels()
{
	return mChannels;
}
