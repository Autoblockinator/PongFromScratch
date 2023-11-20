#pragma once

namespace str_util {
    std::vector<string> split(const char* string, const int& string_size, const char* delim, const int& delim_size);
    std::vector<string> split(const string& string, const char& delim);
    std::vector<string> split(const string& string, const std::string& delim);
}
