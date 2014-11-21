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

void CoreObject::SetPrintPrefix(std::string prefix, enum PrintTypes type)
{
	if(type == FUNC_PRINT) prefix+="() ";
	prefix = mTypePrefix + prefix;

	mSTD.SetPrefix("[STD] " + prefix);
	mDebug.SetPrefix("[DEBUG] " + prefix);
	mWarn.SetPrefix("[WARN] " + prefix);
	mError.SetPrefix("[ERROR] " + prefix);
}
void CoreObject::ClearPrintPrefix()
{
	mSTD.SetPrefix(CoreObject::mSTDPrefix);
	mDebug.SetPrefix(CoreObject::mDebugPrefix);
	mWarn.SetPrefix(CoreObject::mWarningPrefix);
	mError.SetPrefix(CoreObject::mErrorPrefix);
}

std::string CoreObject::TypeID()
{
	return mTypeID;
}
