#include "HttpResource.hpp"
#include <vector>
#include <clews/utility/FileUtil.hpp>
#include <iostream>
#include <fstream>

using namespace std;

HttpResource::HttpResource(std::string url, MimeDB& mimeDB) : mURL(url), mMimeDB(mimeDB), mMimeType(mMimeDB.GetMime(url)) {}

string HttpResource::Content()
{
    return mContent;
}
uint32_t HttpResource::ContentLength()
{
    return mContent.length();
}
MimeType HttpResource::Mime()
{
    return mMimeType;
}
int HttpResource::Load()
{
    int success = 0;
    if(mMimeType.MajorType() == "text")
    {
        vector<string> file = readFile(mURL.data(), success);

        if(success)
        {
            for(int i=0;i<file.size();i++)
            {
                mContent+=file.at(i) + "\r\n";
            }
        }
    }
    else
    {
        ifstream file(mURL.c_str(), ios::in|ios::binary|ios::ate);

        success = file.is_open();
        if (success)
        {
            streampos size = file.tellg();
            char* memblock = new char[size];
            file.seekg (0, ios::beg);
            file.read(memblock, size);
            file.close();

            mContent = string(memblock, size);
            delete memblock;
        }
    }
    return success;
}
