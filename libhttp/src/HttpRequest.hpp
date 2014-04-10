#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#if defined(__sun) && defined(__SVR4)
typedef long id_t;
typedef id_t ctid_t;
typedef id_t zoneid_t;
#endif
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include "UserAgent.hpp"

class HttpRequest
{
private:
    std::string mRequestLine;
    std::string mRequestType;
    std::string mRequestFile;
    std::string mHttpVersion;

    int mStatusCode;
    int mContentLength;
    std::string mDate;
    std::string mContentType;
    std::string mContent;
    std::map<std::string, std::string> mRequestMap;

    std::vector<std::string> mHeaderLines;
    std::vector<std::string> mContentLines;

    void SetContentType(std::string mimeLine);
    void SetContent(std::string contentLine);
    bool ParseRequestLine(std::string requestLine);
public:
    HttpRequest(std::string requestBuffer);

    std::string RequestType();
    std::string RequestedFile();
    std::string HttpVersion();
    UserAgent UserAgentObj();

    std::string HeaderField(std::string fieldName);
    std::string operator[](std::string fieldName);

    std::string Header();
    std::string Content();
    std::string FullResponse();

    void PrintHeader();
};

#endif
