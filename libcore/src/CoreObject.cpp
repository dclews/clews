#include "CoreObject.hpp"

const char* CoreObject::mSTDPrefix =  "[STD] ";
const char* CoreObject::mWarningPrefix = "[WARN] ";
const char* CoreObject::mDebugPrefix = "[DEBUG] ";
const char* CoreObject::mErrorPrefix = "[ERROR] ";

CoreObject::CoreObject(std::string typeID) : mTypeID(typeID), mSTD(std::cout, true), mDebug(std::cerr, false), mWarn(std::cerr, true), mError(std::cerr, true), mTypePrefix("[" + mTypeID + "] ")
{
	mDebug.SetPrefix("[DEBUG] ");
	mWarn.SetPrefix("[WARN] ");
	mError.SetPrefix("[ERROR] ");
}
CoreObject::~CoreObject() {}

CoreStream& CoreObject::StandardOut()
{
//    std::cout << "StandardOut()" << std::endl;
	return mSTD;
}
CoreStream& CoreObject::DebugOut()
{
//    std::cout << "DebugOut()" << std::endl;
	return mDebug;
}
CoreStream& CoreObject::WarningOut()
{
//    std::cout << "WarningOut()" << std::endl;
	return mWarn;
}
CoreStream& CoreObject::ErrorOut()
{
//    std::cout << "ErrorOut()" << std::endl;
	return mError;
}

void CoreObject::SetPrintPrefix(std::string prefix, PrintTypes type)
{
	if(type == FUNC_PRINT) prefix+="() ";
	mPrefix = mTypePrefix + prefix;

	mSTD.SetPrefix("[STD] " + mPrefix);
	mDebug.SetPrefix("[DEBUG] " + mPrefix);
	mWarn.SetPrefix("[WARN] " + mPrefix);
	mError.SetPrefix("[ERROR] " + mPrefix);
}
void CoreObject::ClearPrintPrefix()
{
	mSTD.SetPrefix(CoreObject::mSTDPrefix);
	mDebug.SetPrefix(CoreObject::mDebugPrefix);
	mWarn.SetPrefix(CoreObject::mWarningPrefix);
	mError.SetPrefix(CoreObject::mErrorPrefix);
}
void CoreObject::PushPrintPrefix(std::string prefix, PrintTypes type)
{
	mPrefixStack.push_back(make_pair(mPrefix, type));
	SetPrintPrefix(prefix, type);
}
void CoreObject::PopPrintPrefix()
{
	std::pair<std::string, PrintTypes> newPrefix = mPrefixStack.back();
	if(mPrefixStack.empty())
	{
		ClearPrintPrefix();
	}
	else
	{
		SetPrintPrefix(newPrefix.first, newPrefix.second);
		mPrefixStack.pop_back();
	}
}

std::string CoreObject::TypeID()
{
	return mTypeID;
}
