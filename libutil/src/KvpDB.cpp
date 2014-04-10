#include "KvpDB.hpp"
#include <iostream>

using namespace std;

KvpDB::KvpDB(std::string typeID, char delim) : CoreObject(typeID), mDelimiter(delim) {}

bool KvpDB::Load(const char* dbPath)
{
    SetPrintPrefix(__func__, FUNC_PRINT);

    bool ret = false;
    int success;
    vector<string> fileBuffer = readFile(dbPath, success);
    if(success)
    {
        mKvpMap.clear();
        for(unsigned int i=0;i<fileBuffer.size();++i)
        {
            vector<string> splitLine = split(fileBuffer.at(i), mDelimiter);

            if(splitLine.size() == 2)
            {
                mKvpMap[splitLine.at(0)] = splitLine.at(1);
            }
            else
            {
                ErrorOut() << "Malformed entry: " << fileBuffer[i] << " from DB: " << dbPath << endl;
            }
        }
        mLoadedDBPath = dbPath;
        ret = true;
        StandardOut() << "Loaded DB from: " << dbPath << endl;
    }
    else
    {
        ErrorOut() << "Failed to read DB file: " << dbPath << endl;
    }

    ClearPrintPrefix();
    return ret;
}
bool KvpDB::Load(const std::string& dbPath)
{
    return Load(dbPath.data());
}
bool KvpDB::Reload()
{
    SetPrintPrefix(__func__, FUNC_PRINT);
    StandardOut() << "Reloading DB: " << mLoadedDBPath << endl;
    ClearPrintPrefix();
    return Load(mLoadedDBPath.data());
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
    return value;
}
int KvpDB::GetInt(const char* key)
{
    int iVal = 0;
    try
    {
        iVal = std::stoi(Get(key));
    }
    catch(exception e)
    {
        ErrorOut() << "Failed to convert key '" << key << "' to int" << endl;
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
