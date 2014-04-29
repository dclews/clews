#include "HttpRequest.hpp"
#include <stdlib.h>
#include <clews/utility/StringUtil.hpp>

using namespace std;

HttpRequest::HttpRequest(std::string requestBuffer)
{
    vector<string> requestLinesBuffer = split(requestBuffer, '\n');

    if(requestLinesBuffer.size() > 0)
    {
        mRequestLine = requestLinesBuffer.at(0);
        ParseRequestLine(mRequestLine);
    }

    size_t i=1;
    while(i<requestLinesBuffer.size() && requestLinesBuffer.at(i) != "\r\n" && !requestLinesBuffer.at(i).empty())
    {
        mHeaderLines.push_back(trimRight(requestLinesBuffer.at(i), "\n"));
        ++i;
    }
    for(;i<requestLinesBuffer.size();++i)
    {
        mContentLines.push_back(requestLinesBuffer.at(i));
    }

    for(size_t h=0;h<mHeaderLines.size();++h)
    {
        string line = mHeaderLines[h];
        size_t delimPos = line.find_first_of(' ');

        if(delimPos != 0 && delimPos != string::npos && delimPos!=line.length()-1)
        {
            string key = line.substr(0, delimPos-1);
            string value = trimLeft(line.substr(delimPos+1), " ");
//            cout << "Key: " << key << endl;
//            cout << "Value: " << value << endl;
            mRequestMap[key] = value;
        }
    }
}

bool HttpRequest::ParseRequestLine(string requestLine)
{
    bool success = false;
    vector<string> splitLine = split(requestLine, ' ');
    if(splitLine.size() > 0)
    {
        if(splitLine.at(0) == "GET" && splitLine.size() == 3)
        {
            mRequestType = "GET";
            mRequestResource = splitLine.at(1);
            mHttpVersion = splitLine.at(2);
        }
    }
    return success;
}

string HttpRequest::RequestType()
{
    return mRequestType;
}
string HttpRequest::RequestedResource()
{
    return mRequestResource;
}
string HttpRequest::HttpVersion()
{
    return mHttpVersion;
}

UserAgent HttpRequest::UserAgentObj()
{
    return UserAgent(HeaderField("User-Agent"));
}
string HttpRequest::HeaderField(string key)
{
    string field;
    map<string,string>::iterator it = mRequestMap.find(key);
    if(it!=mRequestMap.end())
    {
        field = it->second;
    }
    return field;
}

string HttpRequest::operator[](string fieldName)
{
    return HeaderField(fieldName);
}
std::string HttpRequest::Header()
{
    std::string header = mRequestLine + "\r\n";
    for(size_t i=0;i<mHeaderLines.size();++i)
    {
        header+=mHeaderLines.at(i) + "\r\n";
    }
    return header;
}
std::string HttpRequest::Content()
{
    std::string content;
    for(size_t i=0;i<mContentLines.size();++i)
    {
        content+=mContentLines.at(i);
    }
    return content;
}
std::string HttpRequest::FullRequest()
{
    return Header() + "\r\n" + Content();
}
void HttpRequest::PrintHeader()
{
    std::cout << Header() << std::endl;
}
