#include "HttpResourceTemplate.hpp"

using namespace std;

HttpResourceTemplate::HttpResourceTemplate(std::string templateURL, MimeDB& mimeDB, map<string, string> tokens) : HttpResource(templateURL, mimeDB), mTokens(tokens)
{
}
uint32_t HttpResourceTemplate::Load()
{
	uint32_t status = HttpResource::Load();
	ReplaceTokens(mTokens);
	return status;
}
