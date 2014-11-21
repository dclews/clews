#ifndef CLEWS_STRING_UTIL_HPP
#define CLEWS_STRING_UTIL_HPP

#if defined(__sun) && defined(__SVR4)
typedef long id_t;
typedef id_t ctid_t;
typedef id_t zoneid_t;
#endif

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

std::vector<std::string> split(const std::string& s, char delim);
std::vector<std::string> split(const std::string &s, const std::string& delim);
std::vector<std::string>& split(const std::string& s, char delim, std::vector<std::string>& elems);
std::vector<std::string>& split(const std::string& s, const std::string& delim, std::vector<std::string>& elems);
std::string concat(std::vector<std::string> parts, std::string delim);

std::string trimLeft(std::string str, std::string toTrim);
std::string trimRight(std::string str, std::string toTrim);
bool startsWith(const std::string& str, const std::string& prefix);

#endif
