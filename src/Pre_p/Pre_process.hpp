# include "../Include/Overall.h"

std::string __delete_enter(const std::string &_str) {
    std::string ret;
    for (size_t i = 0; i < _str.size(); i++) {
        if (_str[i] >= 32 && _str[i] <= 122) ret.push_back(_str[i]);
        else ret.push_back(' ');
    }
    return ret;
}

std::string __expand_macro(const std::string &_str) {
    static std::unordered_map<std::string, std::string> macro_table = {

    };
    std::string ret;

}