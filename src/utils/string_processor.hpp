#ifndef STRING_PROCESSOR_HPP_INCLUDED
#define STRING_PROCESSOR_HPP_INCLUDED

#include <string>
#include <tuple>
#include <vector>

#include <memory>
#include <stdexcept>

using std::cout;
using std::endl;

std::vector<std::string> split(const std::string& str,
                               const std::string& pattern) {
    std::vector<std::string> res;
    if (str == "") {
        return res;
    }
    std::string strs = str + pattern;
    size_t pos = strs.find(pattern);

    while (pos != strs.npos) {
        std::string temp = strs.substr(0, pos);
        res.push_back(temp);
        strs = strs.substr(pos + pattern.length(), strs.size());
        pos = strs.find(pattern);
    }

    return res;
}

// https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
template <typename... Args>
std::string string_format(const std::string& format, Args... args) {
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;
    if (size_s <= 0) {
        throw std::runtime_error("Error during formatting.");
    }
    auto size = static_cast<size_t>(size_s);
    auto buf = std::make_unique<char[]>(size);
    std::snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1);
}

#endif