#include "IrcClientList.hpp"

using namespace std;
IrcClientList::IrcClientList()
{
}
IrcClient* IrcClientList::ClientByIP(const string& ip)
{
	for(size_t i=0;i<size();++i)
	{
		if(at(i).IP() == ip)
		{
			return &at(i);
		}
	}
	return NULL; //Convert to nullptr when we get C++11 support.
}
IrcClient* IrcClientList::ClientByNick(const string& nick)
{
	for(size_t i=0;i<size();++i)
	{
		if(at(i).Nick() == nick)
		{
			return &at(i);
		}
	}
	return NULL; //Convert to nullptr when we get C++11 support.
}
IrcClient* IrcClientList::ClientByUser(const string& user)
{
	for(size_t i=0;i<size();++i)
	{
		if(at(i).User() == user)
		{
			return &at(i);
		}
	}
	return NULL; //Convert to nullptr when we get C++11 support.
}
