#ifndef HTTP_RESOURCE_TEMPLATE_HPP
#define HTTP_RESOURCE_TEMPLATE_HPP

#include "HttpResource.hpp"
#include <map>
#include <string>

class HttpResourceTemplate : public HttpResource
{
private:
    std::map<std::string, std::string> mTokens;
public:
    HttpResourceTemplate(std::string url, Server& mimeDB, std::map<std::string, std::string> tokens=std::map<std::string, std::string>());
    int Load();
};

#endif
