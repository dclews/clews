#include "StringUtil.hpp"

using namespace std;

vector<string> split(const string& s, char delim)
{
		vector<string> elems;
		split(s, delim, elems);
		return elems;
}
vector<string>& split(const string& s, char delim, vector<string>& elems)
{
		stringstream ss(s);
		string item;

		while (getline(ss, item, delim))
		{
				elems.push_back(item);
		}
		return elems;
}
vector<string> split(const string &s, const string& delim)
{
		vector<string> elems;
		split(s, delim, elems);
		return elems;
}
vector<string>& split(const string &s, const string& delim, std::vector<string> &elems)
{
		size_t startPos = 0;
		size_t delimPos = 0;
		std::string token;
		while ((delimPos = s.find(delim, startPos)) != std::string::npos)
		{
				token = trimRight(trimLeft(s.substr(startPos, delimPos), delim), delim);
				if(!token.empty())
				{
					cout << "Adding token: " << token << endl;
					elems.push_back(token);
				}
				startPos = delimPos + delim.length();
		}
		if(startPos < s.length()) //Get the last token if it exists.
		{
			elems.push_back(s.substr(startPos, string::npos));
		}

		return elems;
}

string trimRight(string str, string toTrim)
{
		str.erase(str.find_last_not_of(toTrim)+1);
		return str;
}
string trimLeft(string str, string toTrim)
{
	string trimmed;
	size_t pos = str.find_first_not_of(toTrim.c_str());

	if(!str.empty() && pos != string::npos)
	{
			trimmed = str.substr(pos);
	}
	else
	{
		cout << "trimLeft: Returning empty string" << endl;
	}

	return trimmed;
}
bool startsWith(const string& str, const string& prefix)
{
		return (str.substr(0, prefix.size()) == prefix);
}
string concat(std::vector<string> parts, string delim)
{
		std::string full;
		for(size_t i=0;i<parts.size();++i)
		{
				full+=parts.at(i)+delim;
		}
		return full;
}
