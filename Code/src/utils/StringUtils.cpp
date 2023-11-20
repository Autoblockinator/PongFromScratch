#include <utils/Basic.hpp>
#include <utils/StringUtils.hpp>

std::vector<string> str_util::split(const char* string, const int& string_size, const char* delim, const int& delim_size) {
    std::vector<std::string> out;
    std::string string_buffer;
    int delim_buffer;

    auto flushDelimBuffer = [&string_buffer, &delim_buffer, delim]() -> void {
        if (delim_buffer == 0) { return; }
        for (int i = 0; i < delim_buffer; i++) { string_buffer.push_back(delim[i]); }
        delim_buffer = 0;
    };
    auto flushStringBuffer = [&flushDelimBuffer, &string_buffer, &out](bool soft = false) -> void {
        flushDelimBuffer();
        if ((string_buffer.size() == 0) && soft) { return; }
        out.push_back(string_buffer);
        string_buffer.clear();
    };

    for (int i = 0; i < string_size; i++) {
        if (delim_buffer == 0) {
            if (string[i] == delim[0]) {
                if (delim_size == 1) { flushStringBuffer(); }
                else { delim_buffer++; }
            } else { string_buffer.push_back(string[i]); }
            continue;
        }
        if (string[i] == delim[delim_buffer]) {
            delim_buffer++;
            if (delim_buffer == delim_size) { delim_buffer = 0; flushStringBuffer(); }
            continue;
        }
        flushDelimBuffer();
        string_buffer.push_back(string[i]);
    }
    flushStringBuffer(true);

    return out;
}
std::vector<string> str_util::split(const string& string, const char& delim) { return split(string.c_str(), string.size(), &delim, 1); }
std::vector<string> str_util::split(const string& string, const std::string& delim) { return split(string.c_str(), string.size(), delim.c_str(), delim.size()); }
