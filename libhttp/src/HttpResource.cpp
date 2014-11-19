#include "HttpResource.hpp"
#include <vector>
#include <clews/utility/FileUtil.hpp>
#include <iostream>
#include <fstream>
#include <clews/http/HttpCommon.hpp>

using namespace std;

HttpResource::HttpResource(std::string url, MimeDB& mimeDB) : CoreObject("HttpResource") ,mURL(url), mMimeDB(mimeDB), mMimeType(mMimeDB.GetMime(url)) {}

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
	uint32_t httpStatus = HTTP_SERVER_ERROR;

	if(mMimeType.MajorType() == "text")
	{
		int fileLoadStatus = FILE_NOT_FOUND;
		vector<string> file = readFile(mURL.data(), fileLoadStatus);

		if(fileLoadStatus == FILE_LOADED)
		{
			for(size_t i=0;i<file.size();i++)
			{
				mContent+=file.at(i) + "\r\n";
			}
		}

		httpStatus = (fileLoadStatus == FILE_LOADED) ? HTTP_OK : HTTP_NOT_FOUND;
	}
	else
	{
		ifstream file(mURL.c_str(), ios::in|ios::binary|ios::ate);

		if (file.is_open())
		{
			streampos size = file.tellg();
			char* memblock = new char[size];
			if(memblock == NULL)
			{
				DebugOut() << "Allocation error" << endl;
			}
			else
			{
				file.seekg (0, ios::beg);
				file.read(memblock, size);
				file.close();

				mContent = string(memblock, size);
				delete memblock;
				memblock=NULL;

				httpStatus = HTTP_OK;
			}
		}
	}
	return httpStatus;
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
