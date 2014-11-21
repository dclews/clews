#include "UserAgent.hpp"

using namespace std;

UserAgent::UserAgent(string rawUA) : mRawUA(rawUA) {}

string UserAgent::RawUA()
{
	return mRawUA;
}

string UserAgent::BrowserFamily()
{
	const char* families[] = {"Mozilla"}; int numElems = 1;
	std::string family = FindField(families, numElems);
	return !family.empty() ? family : "Unknown";
}

string UserAgent::OperatingSystem()
{
	const char* OSs[] = {"Linux", "Windows",}; int numElems = 2;
	std::string os = FindField(OSs, numElems);
	return !os.empty() ? os : "Unknown";
}
string UserAgent::SystemArchitecture()
{
	return "Unknown";
}

string UserAgent::RenderingEngine()
{
	const char* engines[] = {"Gecko", "Trident",}; int numElems = 2;
	std::string engine = FindField(engines, numElems);
	return !engine.empty() ? engine : "Unknown";
}

string UserAgent::FindField(const char** elems, size_t numElems)
{
	std::string field;
	for(size_t i=0;i<numElems;++i)
	{
		size_t pos = mRawUA.find(elems[i]);
		if(pos != string::npos)
		{
			field = elems[i];
			break;
		}
	}
	return field;
}

