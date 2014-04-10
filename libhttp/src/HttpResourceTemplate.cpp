#include "HttpResourceTemplate.hpp"

using namespace std;

HttpResourceTemplate::HttpResourceTemplate(std::string templateURL, MimeDB& mimeDB, map<string, string> tokens) : HttpResource(templateURL, mimeDB), mTokens(tokens)
{
}
int HttpResourceTemplate::Load()
{
    int success = HttpResource::Load();
    ReplaceTokens(mTokens);
    return success;
}
