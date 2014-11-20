#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#if defined(__sun) && defined(__SVR4)
typedef long id_t;
typedef id_t ctid_t;
typedef id_t zoneid_t;
#endif
#include <string>
#include "HttpResponseDB.hpp"
#include "HttpResource.hpp"
#include <ctime>

class HttpResponse
{
private:
	HttpResponseDB& mStatusDB;
	std::string mHttpVersion;
	uint32_t mStatusCode;
	uint32_t mContentLength;

	std::string mDate;
	std::string mContentType;
	std::string mContent;
public:
	HttpResponse(std::string httpVersion, HttpResponseDB& db);
	void SetStatusCode(uint32_t code);
	void SetDate(std::string date);
	void SetContentType(std::string mime);
	void SetContent(std::string content);
	void SetContent(HttpResource& res);

	uint32_t StatusCode();
	std::string StatusLine();
	std::string DateLine();
	std::string ContentTypeLine();
	std::string ContentLengthLine();
	std::string Header();
	std::string Content();
	std::string FullResponse();

	void PrintHeader();
	void PrintContent();
	void SetDate(std::tm* lcltime);
	bool OK();
};

#endif
