#include "HttpResource.hpp"
#include <vector>
#include <clews/utility/FileUtil.hpp>
#include <iostream>
#include <fstream>
#include <clews/http/HttpCommon.hpp>

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
uint32_t HttpResource::Load()
{
		int fileLoadStatus = FILE_NOT_FOUND;
		if(mMimeType.MajorType() == "text")
		{
				vector<string> file = readFile(mURL.data(), fileLoadStatus);

				if(fileLoadStatus == FILE_LOADED)
				{
						for(size_t i=0;i<file.size();i++)
						{
								mContent+=file.at(i) + "\r\n";
						}
				}
		}
		else
		{
				ifstream file(mURL.c_str(), ios::in|ios::binary|ios::ate);

				fileLoadStatus = file.is_open() ? FILE_LOADED : FILE_NOT_FOUND;
				if (fileLoadStatus == FILE_LOADED)
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
		return fileLoadStatus == FILE_LOADED ? HTTP_OK : HTTP_NOT_FOUND;
}
void HttpResource::ReplaceTokens(map<string, string> tokenMap)
{
		map<string, string>::iterator tokIt;
		for(tokIt=tokenMap.begin();tokIt!=tokenMap.end();++tokIt)
		{
				size_t strPos = mContent.find(tokIt->first);
				if(strPos != string::npos)
				{
						mContent.replace(strPos, strPos+tokIt->first.length(), tokIt->second);
				}
		}
}
