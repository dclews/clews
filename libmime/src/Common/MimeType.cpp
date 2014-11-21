#include "MimeType.hpp"
#include <clews/utility/StringUtil.hpp>

using namespace std;

MimeType::MimeType(std::string rawMime)
{
    vector<string> splitMime = split(rawMime, '/');
    if(splitMime.size() != 2)
    {
        mValid = false;
        mMajorType = "application";
        mSubType = "octet-stream";
    }
    else
    {
        mMajorType = splitMime.at(0);
        mSubType = splitMime.at(1);
    }
}

string MimeType::MajorType()
{
    return mMajorType;
}

string MimeType::SubType()
{
    return mSubType;
}

string MimeType::RawType()
{
    return mMajorType + "/" + mSubType;
}
bool MimeType::IsValid()
{
    return mValid;
}
