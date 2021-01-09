# pragma once
# include "../Include/Overall.h"

AMIC_NAMESPACE_START

template <class key, class value>
using hash = std::unordered_map<key, value>;
template <class key>
using set = std::set<key>;

class functions {
    static hash<std::string, double(*)(const std::vector<double>&)> func_table;
    static set<char> oper_char_table;
public:
    static inline double sin(const std::vector<double>& para) { 
        if (para.size() > 1) {
            std::cout << "(Ami0031) Semantic warning: too much parameters in function \"sin\"" << "\n";
        }
        if (para.size() < 1) {
            std::cout << "(Ami0032) Semantic error: too few parameters in function \"sin\"" << "\n";
            throw(3);
        }
        return std::sin(para.front()); 
    }
    static inline double cos(const std::vector<double>& para) { return std::cos(para.front()); }
    static inline double power(const std::vector<double>& para) { 
        if (para.size() < 2) {
            std::cout << "(Ami0032) Semantic error: too few parameters in function \"power\"" << "\n";
            throw(3);
        }
        return std::pow(para[0], para[1]);
    }
    friend bool is_function(const std::string &_str);
    friend double(*get_function(const std::string &_str))(const std::vector<double>&);
    friend bool is_oper_char(char c);
    friend void __insert_function(const std::string &id, double(*f)(const std::vector<double>&));
};
hash<std::string, double(*)(const std::vector<double>&)> functions::func_table = {
    {"sin", functions::sin}, {"cos", functions::cos}, {"power", functions::power}, {"pow", functions::power}
};
set<char> functions::oper_char_table = {'+', '-', '*', '/', '%', '(', ')', '\\', ','};
bool is_function(const std::string &_str) {
    return functions::func_table.find(_str) != functions::func_table.end(); 
}
double(*get_function(const std::string &_str))(const std::vector<double>&) {
    return functions::func_table[_str];
}
void __insert_function(const std::string &id, double(*f)(const std::vector<double>&)) {
    functions::func_table[id] = f;
}

inline bool is_oper_char(char c) {
    return functions::oper_char_table.find(c) != functions::oper_char_table.end(); 
}
inline bool is_digit(char c) { return c >= '0' && c <= '9'; }
inline bool is_alpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }


namespace token {

enum token_type { error = -2, end = -1, base = 0, inter = 1, flo = 2, oper = 3, function = 4, 
    add = '+', sub = '-', muitl = '*', div = '/', reme = '%', left = '(', right = ')', int_div = '\\', comma = ',' 
};

class token {
protected:
    token_type type;
public:
    token() : type(base) {};
    explicit token(token_type tt = base) : type(tt) {}; 
    inline token_type getTokenType() { return type; }
    virtual void printToken() { std::cout << "token type: " << (int)type << " \t"; }
};

class error_token : public token {
protected:
    std::string error_string;
    size_t error_begin;
public:
    error_token(const std::string& _str, size_t loca) : token(error), error_string(_str), error_begin(loca) { }
    void printToken() override {
        token::printToken();
        if (!error_string.empty()) std::cout << "invalid function: " << error_string << "\t";
        std::cout << "error location: " << error_begin << "\n";
    }
};

class int_token : public token {
protected:
    int lexical_info;
public:
    explicit int_token(const std::string &_str) : token(inter), lexical_info(std::stoi(_str)) { }
    void printToken() override {
        token::printToken();
        std::cout << "lexical info: " << lexical_info << "\n";
    }
    int value() { return lexical_info; }
};

class float_token : public token {
protected:
    double lexical_info;
public:
    explicit float_token(const std::string &_str) : token(flo), lexical_info(std::stod(_str)) { }
    void printToken() override {
        token::printToken();
        std::cout << "lexical info: " << lexical_info << "\n";
    }
    double value() { return lexical_info; }
};

class operator_token : public token {
protected:
    char lexical_info;
public:
    explicit operator_token(const std::string &_str) : token(token_type(_str.front())), lexical_info(_str.front()) { }
    void printToken() override {
        token::printToken();
        std::cout << "lexical info: " << lexical_info << "\n";
    }
    char value() { return lexical_info; }
};

class function_token : public token {
protected:
    double (*target_function)(const std::vector<double>&);
    std::string lexical_info;
public:
    explicit function_token(const std::string &_str) : token(function), lexical_info(_str){ 
        // 应该在构造之前就确定_str是否在散列中->语义问题
        target_function = ::AMIC_NAMESPACE::get_function(_str);
    }
    void printToken() override {
        token::printToken();
        std::cout << "lexical info: " << lexical_info << "\n";
    }
    double (*value())(const std::vector<double>&) { return target_function; }
};

};//namespace token

AMIC_NAMESPACE_END  