# pragma once
# include "../Lexical/Lexical_main.hpp"

AMIC_NAMESPACE_START

class production {
public:
    enum non_end {
        End = -1, Root = 0, RootRight = 1, Expr = 2, Factor = 3, ExprRight = 4, 
        Element = 5, Para = 6, Para1 = 7
    };
private:
    static hash<non_end, set<token::token_type>> FIRST_set;
    static hash<non_end, set<token::token_type>> FOLLOW_set;
public:
    static bool in_follow_set(non_end _left, token::token_type _end) {
        return FOLLOW_set[_left].find(_end) != FOLLOW_set[_left].end();
    }
    static bool in_first_set(non_end _left, token::token_type _end) {
        return FIRST_set[_left].find(_end) != FIRST_set[_left].end();
    }
};
hash<production::non_end, set<token::token_type>> production::FOLLOW_set = {
    { Root, { token::right, token::comma, token::end } },
    { RootRight, { token::right, token::comma, token::end } },
    { Expr, { token::add, token::sub, token::end, token::right } },
    { Factor, { token::muitl, token::div, token::int_div, token::reme } },
    { ExprRight, { token::add, token::sub, token::end, token::right, token::comma } },
    { Element, { token::muitl, token::div, token::int_div, token::reme } },
    { Para, { token::right } },
    { Para1, { token::right } }
};
hash<production::non_end, set<token::token_type>> production::FIRST_set = {
    { Root, { token::left, token::inter, token::flo, token::function, token::sub } },
    { RootRight, { token::add, token::sub } },
    { Expr, { token::left, token::function, token::inter, token::flo } },
    { Factor, { token::left, token::inter, token::flo, token::function } },
    { ExprRight, { token::muitl, token::div, token::int_div, token::reme } },
    { Element, { token::left, token::inter, token::flo } },
    { Para, { token::comma } },
    { Para1, { token::left } }
};

namespace T_node {

class tree_node {
private:
    production::non_end node_type = production::End;
    bool good_node = true;
public:
    virtual double value() = 0;
    tree_node(production::non_end _nt) : node_type(_nt) { }
    std::vector<tree_node*> childs;
    production::non_end get_node_type() { return node_type; }
};

class root_node : public tree_node {
private:
    bool negative = false;
public:
    root_node() : tree_node(production::Root) { }
    void set_negative() { negative = true; }
    double value() {
        double ret = childs[0]->value();
        ret = negative ? 0 - ret : ret;
        if (childs.size() > 1) ret += childs[1]->value();
        return ret;
    }
};

class rootright_node : public tree_node {
private:
    bool negative = false;
public:
    rootright_node() : tree_node(production::RootRight) { }
    void set_negative() { negative = true; }
    double value() {
        double ret = childs[0]->value();
        if (childs.size() > 1) ret += childs[1]->value();
        return negative ? 0 - ret : ret;
    }
};

class exprright_node : public tree_node {
public:
    char oper;
    exprright_node(char _oper) : tree_node(production::ExprRight), oper(_oper) { }
    double value() {
        double ret = childs[0]->value();
        if (childs.size() == 1) return ret;
        char oper = static_cast<exprright_node*>(childs[1])->oper;
        if (oper == '*') {
            ret *= childs[1]->value();
        } else if (oper == '/') {
            ret /= childs[1]->value();
        } else if (oper == '\\') {
            ret = static_cast<int>(ret / childs[1]->value());
        } else if (oper == '%') {
            ret = ret - static_cast<int>(ret / childs[1]->value());
        }
        return ret;
    }
};

class expr_node : public tree_node {
public:
    expr_node() : tree_node(production::Expr) { }
    double value() {
        double ret = childs[0]->value();
        if (childs.size() == 1) return ret;
        char oper = static_cast<exprright_node*>(childs[1])->oper;
        if (oper == '*') {
            ret *= childs[1]->value();
        } else if (oper == '/') {
            ret /= childs[1]->value();
        } else if (oper == '\\') {
            ret = static_cast<int>(ret / childs[1]->value());
        } else if (oper == '%') {
            ret = ret - childs[1]->value() * static_cast<int>(ret / childs[1]->value());
        }
        return ret;
    }
};

class para_node : public tree_node {
public:
    para_node() : tree_node(production::Para) { }
    double value() { 
        std::cout << "(Ami100) Inner error\n";
        throw(100);
    } // 语义错误才会调用这个
    std::vector<double> para_list() {
        if (this->childs.empty()) return { };
        std::vector<double> ret;
        ret.push_back(this->childs[0]->value());
        if (childs.size() == 1) return ret;
        std::vector<double> right = static_cast<para_node*>(childs[1])->para_list();
        std::for_each(right.begin(), right.end(), [&ret](double temp) {
            ret.push_back(temp);
            });
        return ret;
    }
};

class factor_node : public tree_node {
private:
    double(*func)(const std::vector<double>&) = 0;
public: 
    factor_node() : tree_node(production::Factor) { }
    factor_node(double(*_func)(const std::vector<double>&)) 
        : tree_node(production::Factor), func(_func) { }
    double value() {
        if (func == 0) return childs.front()->value();
        else return func(static_cast<para_node*>(childs[0])->para_list());
    }
};

class element_node : public tree_node {
private:
    double digit = 0;
    bool isDigit = false;
public:
    element_node() : tree_node(production::Element) { }
    element_node(double _dig) : tree_node(production::Element), digit(_dig), isDigit(true) { } 
    double value() {
        return isDigit ? digit : childs[0]->value();
    }
};

};

AMIC_NAMESPACE_END