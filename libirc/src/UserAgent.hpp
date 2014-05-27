#ifndef USER_AGENT_HPP
#define USER_AGENT_HPP

#include <string>

class UserAgent
{
private:
    std::string mRawUA;
    std::string FindField(const char** elems, size_t numElems);
public:
    UserAgent(std::string rawUA);
    std::string RawUA();
    std::string BrowserFamily();
    std::string OperatingSystem();
    std::string SystemArchitecture();
    std::string RenderingEngine();
};

#endif
