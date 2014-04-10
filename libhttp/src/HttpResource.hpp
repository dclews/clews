#ifndef HTTP_RESOURCE_HPP
#define HTTP_RESOURCE_HPP

#include <string>
#include <clews/mime/MimeDB.hpp>
#include <clews/mime/MimeType.hpp>

class HttpResource
{
private:
    std::string mURL;
    std::string mContent;

    MimeDB& mMimeDB;
    MimeType mMimeType;

public:
    HttpResource(std::string url, MimeDB& mimeDB);
    std::string Content();
    uint32_t ContentLength();
    MimeType Mime();
    int Load();
};

#endif

