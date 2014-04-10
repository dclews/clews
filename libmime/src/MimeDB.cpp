#include "MimeDB.hpp"

using namespace std;

MimeDB::MimeDB() : KvpDB("MimeDB", '\t')
{
}
MimeType MimeDB::GetMime(const string& filePath)
{
    string mimeType;

    unsigned pos = filePath.rfind('.');
    if(pos != string::npos)
    {
        string searchCode(filePath.substr(pos));
        mimeType = Get(searchCode);
    }
    if(mimeType.length() < 1)
    {
        mimeType = "application/octet-stream";
    }
    MimeType mime(mimeType);
    return mime;
}
