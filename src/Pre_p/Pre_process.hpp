# include "../Include/Overall.h"

AMIC_NAMESPACE_START

std::string __delete_enter(const std::string &_str) {
    std::string ret;
    for (size_t i = 0; i < _str.size(); i++) {
        if (_str[i] >= 32 && _str[i] <= 122) ret.push_back(_str[i]);
        else ret.push_back(' ');
    }
    return ret;
}

class macro_finder {
    static std::unordered_map<std::string, std::string> macro_table;
public:
    friend bool is_in_macro_table(const std::string &_str);
    friend std::string get_expand(const std::string &_str);
    friend void insert_macro(const std::string &_macro, const std::string &_value);
};
std::unordered_map<std::string, std::string> macro_finder::macro_table = {
    {"e", "2.718281828"}, {"pi", "3.14159265"}
};
bool is_in_macro_table(const std::string &_str) {
    return macro_finder::macro_table.find(_str) != macro_finder::macro_table.end();
}
std::string get_expand(const std::string &_str) {
    return macro_finder::macro_table[_str];
}
void insert_macro(const std::string &_macro, const std::string &_value) {
    macro_finder::macro_table[_macro] = _value;
}

std::string __expand_macro(const std::string &_str) {
    std::string ret;
    bool in_macro_state = false;
    std::string now_macro;
    for (size_t i = 0; i < _str.size(); i++) {
        if (!in_macro_state) {
            if (_str[i] == '$') {
                in_macro_state = true;
                continue;
            } else {
                ret.push_back(_str[i]);
            }
        } else {
            if (_str[i] == '$') {
                in_macro_state = false;
                if (!is_in_macro_table(now_macro)) {
                    std::cout << "(Ami004) Preprocesser error: undefined marco: " << now_macro << "\n";
                    throw(1);
                }
                std::string transformed_string = get_expand(now_macro);
                now_macro.clear();
                ret += transformed_string;
            } else {
                now_macro.push_back(_str[i]);
            }
        }
    }
    if (in_macro_state) {
        std::cout << "(Ami005) Preprocesser error: unclosed macro: " << now_macro << "\n";
        throw(1);
    }
    return ret;
}

std::string pre_process(const std::string &_str) {
    return __expand_macro(__delete_enter(_str));
}

AMIC_NAMESPACE_END