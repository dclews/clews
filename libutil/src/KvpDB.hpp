#ifndef KVP_DB_HPP
#define KVP_DB_HPP

#include <clews/core/CoreObject.hpp>
#include "FileUtil.hpp"
#include "StringUtil.hpp"
#include <map>
#include <string>
#include <mutex>

class KvpDB : public CoreObject
{
private:
    std::map<std::string, std::string> mKvpMap;
    std::string mDelimiter;
    std::string mLineEnd;
    std::string mLoadedDBPath;
    std::mutex mRWLock;
public:
    KvpDB(std::string typeIDv="KvpDB", std::string delim="=", std::string lineEnd="\n");
    virtual bool LoadFile(const char* dbPath);
    bool LoadFile(const std::string& dbPath);
    virtual bool Reload();

    std::string LoadedDBPath();
    std::string Get(const char* key);
    std::string Get(const std::string& key);

    int GetInt(const char* key);
    int GetInt(const std::string& key);

    std::map<std::string, std::string>& RawMap();

    std::string operator [](const char* key);
    void Print();
    std::string ToString();
    bool Load(std::string buffer);
    bool Load(std::vector<std::string>& fileLines);
};

#endif
