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
string trimRight(string str, string toTrim)
{
    str.erase(str.find_last_not_of(toTrim)+1);
    return str;
}
string trimLeft(string str, string toTrim)
{
    size_t pos = str.find_first_not_of(toTrim.c_str());
    if(!str.empty() && pos != string::npos)
    {
        str.substr(pos);
    }
    return str;
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
