#include "IrcClient.hpp"
#include <iostream>

using namespace std;

IrcClient::IrcClient(string ip) : mIP(ip) {}

string IrcClient::IP() {return mIP;}
string IrcClient::User() {return mUser;}
string IrcClient::Nick() {return mNick;}
string IrcClient::Pass() {return mPass;}
string IrcClient::Realname() {return mRealname;}

ModeFlags IrcClient::Modes() {return mModes.bitfield;}
uint8_t IrcClient::OctalModes() {return mModes.octal;}

void IrcClient::SetIP(string ip) {mIP = ip;}
void IrcClient::SetUser(string user) {mUser = user;}
void IrcClient::SetNick(string nick) {mNick = nick;}
void IrcClient::SetPass(string pass) {mPass = pass;}
void IrcClient::SetRealname(string realname) {mRealname = realname;}

void IrcClient::SetModes(uint8_t modes) {mModes.octal=modes;}
void IrcClient::SetModes(ModeFlags modes) {mModes.bitfield=modes;}
void IrcClient::SetModes(ModeFlagsUnion modes){mModes.octal=modes.octal;}

bool IrcClient::IsRegistered()
{
	if(mIP.empty())
	{
		cout << "IP is empty" << endl;
	}
	if(mUser.empty())
	{
		cout << "User is empty" << endl;
	}
	if(mNick.empty())
	{
		cout << "Nick is empty" << endl;
	}
	bool registered = !mIP.empty();
	registered &= !mUser.empty();
	registered &= !mNick.empty();
	return registered;
}
