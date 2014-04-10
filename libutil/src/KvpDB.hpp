#ifndef KVP_DB_HPP
#define KVP_DB_HPP

#include <clews/core/CoreObject.hpp>
#include <clews/utility/FileUtil.hpp>
#include <clews/utility/StringUtil.hpp>
#include <map>
#include <string>

class KvpDB : public CoreObject
{
private:
    std::map<std::string, std::string> mKvpMap;
    char mDelimiter;
    std::string mLoadedDBPath;
public:
    KvpDB(std::string typeIDv="KvpDB", char delim='=');
    virtual bool Load(const char* dbPath);
    bool Load(const std::string& dbPath);
    virtual bool Reload();

    std::string LoadedDBPath();
    std::string Get(const char* key);
    std::string Get(const std::string& key);

    int GetInt(const char* key);
    int GetInt(const std::string& key);

    std::string operator [](const char* key);
    void Print();
};

#endif
