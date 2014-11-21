#include "FileUtil.hpp"
#include <errno.h>
#include <stack>

using namespace std;

vector<string> readFile(const char* filePath, int& success)
{
	vector<string> lines;
	string line;
	ifstream file (filePath, ios::in);

	success = FILE_NOT_FOUND; //Not found.

	if(file.is_open())
	{
		while (getline (file,line))
		{
			lines.push_back(line);
		}
		file.close();
		success = FILE_LOADED;
	}

	return lines;
}
vector<string> readFile(const string& filePath, int& success)
{
		return readFile(filePath.data(), success);
}
string getFullPath(const string& relPath)
{
	errno = 0; //Reset errno.

	char* canonicalPathCStr = realpath(relPath.data(), NULL);
	string canonicalPath;
	if(canonicalPathCStr != NULL)
	{
			canonicalPath = canonicalPathCStr;
			delete canonicalPathCStr;
			canonicalPathCStr=NULL;
	}
	else
	{
		std::cerr << "Could not determine canonical path for relpath: " << relPath << endl;
		perror("The reason was: ");
	}
	return canonicalPath;
}


////Incomplete.
//string virtpath(string relPath)
//{
//	string virtpath;
//	stack<string> strippedParts;
//	do
//	{
//		virtpath = getFullPath(relPath);
//	}
//	while(errno = ENOENT && relPath.find_last_of('/') != string::npos);
//	errno = 0;

//	return virtpath;
//}
