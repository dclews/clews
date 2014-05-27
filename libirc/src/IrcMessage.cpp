#include "IrcMessage.hpp"
#include <stdlib.h>
#include <clews/utility/StringUtil.hpp>
#include <stdexcept>
#include <algorithm>

using namespace std;

IrcMessage::IrcMessage() {	cerr << "Creating message" << endl;}
IrcMessage::IrcMessage(std::string requestBuffer)
{
	//cout << "Parsing message. ";
	requestBuffer = trimRight(requestBuffer, "\r\n");
	vector<string> vMessageBuffer = split(requestBuffer, ' ');

	if(vMessageBuffer.empty())
	{
		throw runtime_error("Failed to parse message. Not enough message segments. Message: " + requestBuffer);
	}
	if(vMessageBuffer.front().at(0) == ':')
	{
		cout << "Parsing prefix. ";
		try
		{
			mPrefix = vMessageBuffer.front().substr(1); //Ignore leading ':'
			vMessageBuffer.erase(vMessageBuffer.begin()); //Remove the prefix from the buffer.
		}
		catch(const out_of_range& e)
		{
			throw runtime_error("Failed to parse message. Empty prefix segment. Message: " + requestBuffer);
		}
	}
	try
	{
		cout << "Parsing command. ";
		mCommand = vMessageBuffer.front();
		vMessageBuffer.erase(vMessageBuffer.begin()); //Remove the command from the buffer.
	}
	catch(const out_of_range& e)
	{
		throw runtime_error("Failed to parse message. Empty command segment. Message: " + requestBuffer);
	}
	if(!vMessageBuffer.empty())
	{
		cout << "Parsing params and trailing. ";
		size_t trailingStart = 999; //Token value for not found.
		for(size_t i=0;i<vMessageBuffer.size();++i) //Attempt to find a trailing token.
		{
			if(vMessageBuffer.at(i).at(0) == ':')
			{
				trailingStart = i;
			}
		}
		if(trailingStart != 999)
		{
			vector<string> vTrailing(trailingStart+1);
			//Copy all of the trailing segments to their vector.
			copy(vMessageBuffer.begin()+trailingStart, vMessageBuffer.end(), vTrailing.begin());
			//Remove the trailing segments from the buffer.
			vMessageBuffer.erase(vMessageBuffer.begin()+trailingStart, vMessageBuffer.end());
			//Construct the trailing string from this. Ignoring the leading ':' and trailing ' '.
			mTrailing = concat(vTrailing, " ").substr(1, mTrailing.size()-2);
		}
		mParams = vMessageBuffer; //Store the remaining segments as params.
	}
	//cout << "Done parsing." << endl;
}
string IrcMessage::IrcVersion()
{
//	cout << "IrcVersion()" << endl;
	return mIrcVersion;
}
std::string IrcMessage::Prefix()
{
//	cout << "Prefix()" << endl;
	return mPrefix;
}
std::string IrcMessage::Command()
{
//	cout << "Command()" << endl;
	return mCommand;
}
std::vector<std::string> IrcMessage::Params()
{
//	cout << "Params()" << endl;
	return mParams;
}
string IrcMessage::Trailing()
{
//	cout << "Trailing()" << endl;
	return mTrailing;
}

void IrcMessage::SetPrefix(string prefix)
{
//	cout << "SetPrefix()" << endl;
	mPrefix = prefix;
}
void IrcMessage::SetCommand(string command)
{
	cout << "SetCommand()" << endl;
	mCommand = command;
}

void IrcMessage::SetParams(std::vector<string> params)
{
	cout << "SetParams()" << endl;
	mParams = params;
}

void IrcMessage::SetParams(string params)
{
	cout << "SetParams()" << endl;
	mParams = split(params, ' ');
}

void IrcMessage::SetTrailing(string trailing)
{
	cout << "SetTrailing()" << endl;
	mTrailing = trailing;
}
string IrcMessage::ParamsString()
{
//	cout << "ParamsString()" << endl;
	return trimRight(concat(mParams, " "), " ");
}
string IrcMessage::RawMessageString()
{
	return MessageString() + "\r\n";
}

string IrcMessage::MessageString()
{
	cout << "MessageString()" << endl;
	string msgstr;
	if(!mPrefix.empty())
	{
		msgstr+=":"+mPrefix;
	}
	msgstr+=" " + mCommand; //Can command be empty?
	if(!mParams.empty())
	{
		msgstr+=" "+ParamsString();
	}
	if(!mTrailing.empty())
	{
		msgstr+=" :" + mTrailing; //Trailing MUST be preceded by a space.
	}
	return trimLeft(msgstr, " ");
}
void IrcMessage::Print()
{
	cerr << "Print()" << endl;
	cerr << MessageString() << endl;
}
