#ifndef FILE_UTIL_HPP
#define FILE_UTIL_HPP

#if defined(__sun) && defined(__SVR4)
typedef long id_t;
typedef id_t ctid_t;
typedef id_t zoneid_t;
#endif

#include <ostream>
#include <istream>

#include <iostream>
#include <fstream>

#include <string>
#include <vector>

std::vector<std::string> readFile(const char* filePath, int& success);
std::vector<std::string> readFile(const std::string& filePath, int& success);

std::string getFullPath(const std::string& relPath);

#endif
