#ifndef STRING_PROCESSOR_HPP_INCLUDED
#define STRING_PROCESSOR_HPP_INCLUDED

#include <string>
#include <tuple>
#include <vector>
#include <filesystem>
#include <sstream>
#include <fstream>

#include <memory>
#include <string>
#include <stdexcept>

using std::cout;
using std::endl;
using std::get;
using std::make_tuple;
using std::string;
using std::tuple;
using std::vector;

vector<string> split(const string &str, const string &pattern)
{
    vector<string> res;
    if (str == "")
    {
        return res;
    }
    string strs = str + pattern;
    size_t pos = strs.find(pattern);

    while (pos != strs.npos)
    {
        string temp = strs.substr(0, pos);
        res.push_back(temp);
        strs = strs.substr(pos + pattern.length(), strs.size());
        pos = strs.find(pattern);
    }

    return res;
}

// https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
template <typename... Args>
string string_format(const string &format, Args... args)
{
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;
    if (size_s <= 0)
    {
        throw std::runtime_error("Error during formatting.");
    }
    auto size = static_cast<size_t>(size_s);
    auto buf = std::make_unique<char[]>(size);
    std::snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1);
}

#endif