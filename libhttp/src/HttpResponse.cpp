#include "HttpResponse.hpp"
#include <stdlib.h>
#include <string.h>
#include "HttpCommon.hpp"

HttpResponse::HttpResponse(std::string httpVersion, HttpResponseDB& statusDB) : mStatusDB(statusDB)
{
    mHttpVersion = httpVersion;
    mContentLength = 0;
    mStatusCode = 0;
}
void HttpResponse::SetStatusCode(uint32_t code)
{
    mStatusCode = code;
}
void HttpResponse::SetDate(std::string date)
{
    mDate = date;
}
void HttpResponse::SetDate(tm* lcltime)
{
    char buffer[100];
    strftime(buffer, 100, "%a, %d %b %Y %H:%M:%S GMT", lcltime);
    mDate = std::string(buffer);
}

void HttpResponse::SetContentType(std::string mime)
{
    mContentType = mime;
}
void HttpResponse::SetContent(std::string content)
{
    mContent = content;
    mContentLength = mContent.length();
}

void HttpResponse::SetContent(HttpResource& res)
{
    SetContent(res.Content());
    SetContentType(res.Mime().RawType());
}

uint32_t HttpResponse::StatusCode()
{
    return mStatusCode;
}
std::string HttpResponse::StatusLine()
{
    char buffer[20];
    memset(buffer, 0, 20);
    snprintf(buffer, 20, "%d", mStatusCode);
    return mHttpVersion + " " + buffer + " " + mStatusDB.ResponseString(mStatusCode) + "\r\n";
}
std::string HttpResponse::DateLine()
{
    return "Date: " + mDate + "\r\n";
}
std::string HttpResponse::ContentTypeLine()
{
    return "Content-Type: " + mContentType + "\r\n";
}

std::string HttpResponse::ContentLengthLine()
{
    char buffer[20];
    snprintf(buffer, 20, "%d", mContentLength);
    return "Content-Length: " + std::string(buffer) + "\r\n";
}
std::string HttpResponse::Header()
{
    return StatusLine() + DateLine() + ContentTypeLine() + ContentLengthLine();
}

std::string HttpResponse::Content()
{
    return mContent;
}

std::string HttpResponse::FullResponse()
{
    return Header() + "\r\n" + Content();
}

void HttpResponse::PrintHeader()
{
    std::cout << Header() << std::endl;
}

void HttpResponse::PrintContent()
{
    std::cout << Content() << std::endl;
}

bool HttpResponse::OK()
{
    return mStatusCode == HTTP_OK;
}
