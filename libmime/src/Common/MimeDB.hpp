#ifndef MIME_DB_HPP
#define MIME_DB_HPP

#include <clews/core/CoreObject.hpp>
#include <clews/utility/FileUtil.hpp>
#include <clews/utility/StringUtil.hpp>
#include <clews/utility/KvpDB.hpp>
#include "MimeType.hpp"

class MimeDB : public KvpDB
{
public:
    MimeDB();
    MimeType GetMime(const std::string& filePath);
};

#endif
