#ifndef IRC_CLIENT_HPP
#define IRC_CLIENT_HPP

#include <string>

typedef struct //This nicely fits in a single byte.
{
	uint8_t away : 1; //a
	uint8_t invisible : 1; //i
	uint8_t wallop : 1; //w
	uint8_t restricted : 1; //r
	uint8_t op : 1; //o
	uint8_t localop : 1; //O
	uint8_t notify : 1; //s
} ModeFlags;
union ModeFlagsUnion
{
	ModeFlags bitfield;
	uint8_t octal;
};

class IrcClient
{
private:
	std::string mIP;
	std::string mUser;
	std::string mNick;
	std::string mPass;
	std::string mRealname;
	ModeFlagsUnion mModes;
public:
	IrcClient(std::string ip);
	std::string IP();
	std::string User();
	std::string Nick();
	std::string Pass();
	std::string Realname();
	uint8_t OctalModes();
	ModeFlags Modes();
	void SetIP(std::string ip);
	void SetUser(std::string user);
	void SetNick(std::string nick);
	void SetPass(std::string pass);
	void SetRealname(std::string realname);

	void SetModes(uint8_t modes);
	void SetModes(ModeFlags modes);
	void SetModes(ModeFlagsUnion modes);

	bool IsRegistered();
};

#endif
