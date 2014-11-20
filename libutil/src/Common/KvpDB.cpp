#include "KvpDB.hpp"
#include <iostream>

using namespace std;

KvpDB::KvpDB(std::string typeID, std::string delim, std::string lineEnd) : CoreObject(typeID), mDelimiter(delim), mLineEnd(lineEnd) {}

//!MUTEX
bool KvpDB::LoadFile(const char* dbPath)
{
	mRWLock.lock();
	SetPrintPrefix(__func__, FUNC_PRINT);

	bool ret = false;
	int success;
	vector<string> fileBuffer = readFile(dbPath, success);
	if(success)
	{
		ret = Load(fileBuffer);
		StandardOut() << "Loaded DB from: " << dbPath << endl;
		mLoadedDBPath = dbPath;
	}
	else
	{
		ErrorOut() << "Failed to read DB file: " << dbPath << endl;
	}
	ClearPrintPrefix();

	mRWLock.unlock();
	return ret;
}
bool KvpDB::LoadFile(const std::string& dbPath)
{
	return LoadFile(dbPath.data());
}
bool KvpDB::Load(string buffer)
{
	vector<string> splitLines = split(buffer, mLineEnd);
	return Load(splitLines);
}
bool KvpDB::Load(vector<string>& fileLines)
{
	for(unsigned int i=0;i<fileLines.size();++i)
	{
		vector<string> splitLine = split(fileLines.at(i), mDelimiter);

		if(splitLine.size() == 2)
		{
			mKvpMap[splitLine.at(0)] = splitLine.at(1);
		}
		else
		{
			ErrorOut() << "Malformed entry: " << fileLines.at(i) << endl;
		}
	}
	return true;
}

void KvpDB::Clear()
{
	mKvpMap.clear();
}

bool KvpDB::Reload()
{
	SetPrintPrefix(__func__, FUNC_PRINT);
	StandardOut() << "Reloading DB: " << mLoadedDBPath << endl;
	Clear();
	ClearPrintPrefix();
	return LoadFile(mLoadedDBPath.data());
}

string KvpDB::LoadedDBPath()
{
	return mLoadedDBPath;
}

std::string KvpDB::operator[](const char* key)
{
	string strKey(key);
	return Get(strKey);
}

std::string KvpDB::Get(const char* key)
{
	string strKey(key);
	return Get(strKey);
}
std::string KvpDB::Get(const string& key)
{
	mRWLock.lock();
	SetPrintPrefix(__func__, FUNC_PRINT);
	string value;

	DebugOut() << "Search for string: " << key << endl;

	map<string,string>::iterator it = mKvpMap.find(key);
	//auto it = mKvpMap.find(key);
	if(it != mKvpMap.end())
	{
		value = it->second;
	}
	DebugOut() << "Found string: " << value << endl;
	ClearPrintPrefix();
	mRWLock.unlock();
	return value;
}
int KvpDB::GetInt(const char* key)
{
	int iVal = 0;
	try
	{
		iVal = std::stoi(Get(key));
	}
	catch(const exception& e)
	{
		ErrorOut() << "Failed to convert key '" << key << "' to int" << endl;
		DebugOut() << e.what() << endl;
	}
	return iVal;
}
int KvpDB::GetInt(const string& key)
{
	return GetInt(key.data());
}

std::map<string, string>&KvpDB::RawMap()
{
	return mKvpMap;
}
void KvpDB::Print()
{
	for(map<string, string>::iterator it=mKvpMap.begin();it!=mKvpMap.end();++it)
	{
		StandardOut() << it->first << mDelimiter << it->second << endl;
	}
}

string KvpDB::ToString()
{
	string mapStr;
	for(map<string, string>::iterator it=mKvpMap.begin();it!=mKvpMap.end();++it)
	{
		mapStr+=it->first+mDelimiter+it->second+'\n';
	}
	return mapStr;
}
