# pragma once
# include "Pre_p/Pre_process.hpp"
# include "Tree_Process/Tree_Process_main.hpp"
# include "Parser/Parser_main.hpp"

namespace AmiCal {

void insert_function(const std::string &id, double(*f)(const std::vector<double>&));
void insert_macro(const std::string &macro, const std::string &value);
int get_error_code(const std::string& _expr);
double etod(const std::string& _expr);
float etof(const std::string& _expr);
int32_t etoi(const std::string& _expr);
int print_token(const std::string& _expr);
// void print_tree(const std::string& _expr);

};


namespace AmiCal {

void insert_function(const std::string &id, double(*f)(const std::vector<double>&)) {
    return AMIC_NAMESPACE::__insert_function(id, f);
}

void insert_macro(const std::string &macro, const std::string &value) {
    return AMIC_NAMESPACE::__insert_macro(macro, value);
}

int get_error_code(const std::string& _expr) {
    switch (1) {
    case 1:
        std::string after_pp;
        try { 
            after_pp = AMIC_NAMESPACE::pre_processer::pre_process(_expr); 
            AMIC_NAMESPACE::Lexical_analyzer le_ana(after_pp);
            if (!le_ana.pre_process()) break;
            AMIC_NAMESPACE::Parser par_test(&le_ana);
            AMIC_NAMESPACE::T_node::tree_node* target_tree;
            if (!(target_tree = par_test.get_parser_tree())) {
                break;
            }
            double result = AMIC_NAMESPACE::calcu_tree_value(target_tree);
        } catch (int ec) {
            return ec;
        }
    }
    std::cout << "(Ami000) Complete\n";
    return 0;
}

double etod(const std::string& _expr) {
    switch (1) {
    case 1:
        std::string after_pp;
        try { 
            after_pp = AMIC_NAMESPACE::pre_processer::pre_process(_expr); 
            AMIC_NAMESPACE::Lexical_analyzer le_ana(after_pp);
            if (!le_ana.pre_process()) break;
            AMIC_NAMESPACE::Parser par_test(&le_ana);
            AMIC_NAMESPACE::T_node::tree_node* target_tree;
            if (!(target_tree = par_test.get_parser_tree())) {
                break;
            }
            double result = AMIC_NAMESPACE::calcu_tree_value(target_tree);
            return result;
        } catch (...) {
            break;
        }
    }
    char flag = ' ';
    return nan(&flag);
}

float etof(const std::string& _expr) {
    char flag = ' ';
    double pre_res = etod(_expr);
    if (isnan(pre_res)) return nanf(&flag);
    else return static_cast<float>(pre_res);
}

int32_t etoi(const std::string& _expr) {
    double pre_res = etod(_expr);
    if (isnan(pre_res)) return 0;
    else return static_cast<int32_t>(pre_res);
}

int print_token(const std::string& _expr) {
    AMIC_NAMESPACE::Lexical_analyzer l_ana(_expr);
    AMIC_NAMESPACE::token::token* current;
    while (static_cast<int>((current = l_ana.get_next_token())->getTokenType()) >= 0) {
        current->printToken();
    }
    return current->getTokenType() == AMIC_NAMESPACE::token::end ? 0 : 1; // complete -> 0 | error -> 1
}

/*

void print_tree(const std::string& _expr) {
    switch (1) {
    case 1:
        std::string after_pp;
        try { 
            after_pp = AMIC_NAMESPACE::pre_processer::pre_process(_expr); 
            AMIC_NAMESPACE::Lexical_analyzer le_ana(after_pp);
            if (!le_ana.pre_process()) break;
            AMIC_NAMESPACE::Parser par_test(&le_ana);
            AMIC_NAMESPACE::T_node::tree_node* target_tree;
            if (!(target_tree = par_test.get_parser_tree())) {
                break;
            }

        } catch (...) {
            break;
        }
    }
}

*/

};