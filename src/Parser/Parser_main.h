# pragma once
# include "../Lexical/Lexical_main.h"
# include "Parser_production.hpp"

AMIC_NAMESPACE_START

class Parser {
public:
    tree_node* get_parser_tree();
private:
    Lexical_analyzer* lexical;
    token::token* current_token;
    void error_handle(); // 出错随便抛个啥都行
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

AMIC_NAMESPACE_END