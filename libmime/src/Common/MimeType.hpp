#ifndef MIME_TYPE_HPP
#define MIME_TYPE_HPP

#if defined(__sun) && defined(__SVR4)
typedef long id_t;
typedef id_t ctid_t;
typedef id_t zoneid_t;
#endif
#include <string>

class MimeType
{
private:
    std::string mMajorType;
    std::string mSubType;
    bool mValid;
public:
    MimeType(std::string rawMime);
    std::string MajorType();
    std::string SubType();
    std::string RawType();
    bool IsValid();
};

#endif
