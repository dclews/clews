#include "FileUtil.hpp"

using namespace std;

vector<string> readFile(const char *filePath, int &success)
{
    vector<string> lines;
    string line;
    ifstream file (filePath, ios::in);

    success = 0; //Not found.

    if (file.is_open())
    {
      while ( getline (file,line) )
      {
          lines.push_back(line);
      }
      file.close();
      success = 1;
    }

    return lines;
}
vector<string> readFile(const string& filePath, int& success)
{
    return readFile(filePath.data(), success);
}
string getFullPath(const string& relPath)
{
    char* canonicalPathCStr = realpath(relPath.data(), NULL);
    string canonicalPath;
    if(canonicalPathCStr != NULL)
    {
        canonicalPath = canonicalPathCStr;
        delete canonicalPathCStr;
    }
    else
    {
        std::cerr << "Could not determine canonical path for relpath: " << relPath << endl;
    }
    return canonicalPath;
}
