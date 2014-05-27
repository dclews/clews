#include "IrcChannel.hpp"

IrcChannel::IrcChannel(const std::string& channelName) : mChannelName(channelName) {}
IrcClientList& IrcChannel::Clients() {return mClients;}
