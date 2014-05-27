#ifndef IRC_MESSAGE_HPP
#define IRC_MESSAGE_HPP

#if defined(__sun) && defined(__SVR4)
typedef long id_t;
typedef id_t ctid_t;
typedef id_t zoneid_t;
#endif
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include "UserAgent.hpp"
#include "IrcResponseDB.hpp"

class IrcMessage
{
private:
		std::string mIrcVersion;

		std::string mPrefix;
		std::string mCommand;
		std::vector<std::string> mParams;
		std::string mTrailing;
public:
		IrcMessage();
		IrcMessage(std::string requestBuffer);

		std::string IrcVersion();

		std::string Prefix();
		std::string Command();
		std::vector<std::string> Params();
		std::string Trailing();

		void SetPrefix(std::string prefix);
		void SetCommand(std::string command);
		void SetParams(std::vector<std::string> params);
		void SetParams(std::string params);
		void SetTrailing(std::string trailing);

		std::string ParamsString();
		std::string RawMessageString();
		std::string MessageString();
		void Print();
};

#endif
