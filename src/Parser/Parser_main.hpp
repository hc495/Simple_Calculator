# pragma once
# include "../Lexical/Lexical_main.hpp"
# include "Parser_production.hpp"

AMIC_NAMESPACE_START

class Parser {
public:
    tree_node* get_parser_tree();
private:
    Lexical_analyzer* lexical;
    token::token* current_token;
    void error_handle();
    void delete_null_edge(tree_node* rt);
    
    std::stack<tree_node*> all_node;
    void delete_all_node();
private:
    bool match(token::token_type t_type);
    tree_node* root();
    tree_node* expr();
    tree_node* root_right();
    tree_node* factor();
    tree_node* expr_right();
    tree_node* element();
    tree_node* para();
    tree_node* para1();
public:
    Parser(Lexical_analyzer* _lex);
    ~Parser();
};


Parser::Parser(Lexical_analyzer* _lex) : lexical(_lex) { 
    current_token = lexical->get_next_token();
}

void Parser::error_handle() {
    std::cout << "(Ami002) Syntax Error:";
    lexical->loca_error();
    current_token->printToken();
    std::cout << "\n";
    throw (1);
}

void Parser::delete_null_edge(tree_node* rt) {
    while (!rt->childs.empty() && rt->childs.back() == nullptr) rt->childs.pop_back();
    for (unsigned int i = 0; i < rt->childs.size(); i++) delete_null_edge(rt->childs[i]);
}

Parser::~Parser() {
    delete_all_node();
}

void Parser::delete_all_node() {
    while (!all_node.empty()) {
        delete all_node.top();
        all_node.pop();
    }
}

tree_node* Parser::get_parser_tree() {
    tree_node* ret;
    try {
        ret = root();
        delete_null_edge(ret);
    } catch (...) {
        ret = 0;
    }
    return ret;
}

bool Parser::match(token::token_type t_type) {
    if (current_token->getTokenType() == t_type) {
        current_token = lexical->get_next_token();
        return true;
    } else {
        error_handle();
        return false;
    }
}

tree_node* Parser::root() {
    root_node* ret = new root_node();
    all_node.push(ret);
    if (current_token->getTokenType() == token::sub) {
        ret->set_negative();
        match(token::sub);
        tree_node* left = expr();
        tree_node* right = root_right();
        ret->childs.push_back(left);
        ret->childs.push_back(right);
    } else if (in_first_set(Expr, current_token->getTokenType())) {
        tree_node* left = expr();
        tree_node* right = root_right();
        ret->childs.push_back(left);
        ret->childs.push_back(right);
    } else error_handle();
    return ret;
}

tree_node* Parser::root_right() {
    rootright_node* ret = nullptr;
    if (current_token->getTokenType() == token::add) {
        ret = new rootright_node();
        all_node.push(ret);
        match(token::add);
        tree_node* left = expr();
        tree_node* right = root_right();
        ret->childs.push_back(left);
        ret->childs.push_back(right);
    } else if (current_token->getTokenType() == token::sub) {
        ret = new rootright_node();
        ret->set_negative();
        all_node.push(ret);
        match(token::sub);
        tree_node* left = expr();
        tree_node* right = root_right();
        ret->childs.push_back(left);
        ret->childs.push_back(right);
    } else if (in_follow_set(RootRight, current_token->getTokenType())) {
        return ret;
    } else error_handle();
    return ret;
}

tree_node* Parser::expr() {
    expr_node* ret = new expr_node();
    all_node.push(ret);
    tree_node* fac = factor();
    tree_node* expr_r = expr_right();
    ret->childs.push_back(fac);
    ret->childs.push_back(expr_r);
    return ret;
}

tree_node* Parser::expr_right() {
    exprright_node* ret = nullptr;
    if (current_token->getTokenType() == token::muitl) {
        match(token::muitl);
        ret = new exprright_node('*');
        all_node.push(ret);
        tree_node* fac = factor();
        tree_node* Er = expr_right();
        ret->childs.push_back(fac);
        ret->childs.push_back(Er);
    } else if (current_token->getTokenType() == token::div) {
        match(token::div);
        ret = new exprright_node('/');
        all_node.push(ret);
        tree_node* fac = factor();
        tree_node* Er = expr_right();
        ret->childs.push_back(fac);
        ret->childs.push_back(Er);
    } else if (current_token->getTokenType() == token::int_div) {
        match(token::int_div);
        ret = new exprright_node('\\');
        all_node.push(ret);
        tree_node* fac = factor();
        tree_node* Er = expr_right();
        ret->childs.push_back(fac);
        ret->childs.push_back(Er);
    } else if (current_token->getTokenType() == token::reme) {
        match(token::reme);
        ret = new exprright_node('%');
        all_node.push(ret);
        tree_node* fac = factor();
        tree_node* Er = expr_right();
        ret->childs.push_back(fac);
        ret->childs.push_back(Er);
    } else if (in_follow_set(ExprRight, current_token->getTokenType())) return ret;
    else error_handle();
    return ret;
}

tree_node* Parser::factor() {
    factor_node* ret = nullptr;
    if (in_first_set(Element, current_token->getTokenType())) {
        ret = new factor_node();
        all_node.push(ret);
        tree_node* elem = element();
        ret->childs.push_back(elem);
    } else if (current_token->getTokenType() == token::function) {
        ret = new factor_node(static_cast<token::function_token*>(current_token)->value());
        all_node.push(ret);
        match(token::function);
        match(token::left);
        tree_node* pa = para();
        ret->childs.push_back(pa);
        match(token::right);
    } else error_handle();
    return ret;
}

tree_node* Parser::element() {
    element_node* ret = nullptr;
    if (current_token->getTokenType() == token::left) {
        match(token::left);
        ret = new element_node();
        all_node.push(ret);
        tree_node* rt = root();
        ret->childs.push_back(rt);
        match(token::right);
        return ret;
    } else if (current_token->getTokenType() == token::inter) {
        ret = new element_node(static_cast<token::int_token*>(current_token)->value());
        all_node.push(ret);
        match(token::inter);
        return ret;
    } else if (current_token->getTokenType() == token::flo) {
        ret = new element_node(static_cast<token::float_token*>(current_token)->value());
        all_node.push(ret);
        match(token::flo);
        return ret;
    } else error_handle();
    return ret;
}

tree_node* Parser::para() {
    para_node* ret = new para_node();
    all_node.push(ret);
    if (in_first_set(Root, current_token->getTokenType())) {
        tree_node* left = root();
        tree_node* right = para1();
        ret->childs.push_back(left);
        ret->childs.push_back(right);
    } else if (in_follow_set(Para, current_token->getTokenType())) return ret;
    else error_handle();
    return ret;
}

tree_node* Parser::para1() {
    para_node* ret = nullptr;
    if (current_token->getTokenType() == token::comma) {
        ret = new para_node();
        all_node.push(ret);
        match(token::comma);
        tree_node* left = root();
        tree_node* right = para1();
        ret->childs.push_back(left);
        ret->childs.push_back(right);
        return ret;
    } else if (in_follow_set(Para1, current_token->getTokenType())) return ret;
    else error_handle();
    return ret;
}

AMIC_NAMESPACE_END