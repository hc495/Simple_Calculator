# pragma once
# include "Tree_Process/Tree_Process_main.hpp"

AMIC_NAMESPACE_START

double etod(const std::string& _expr) {
    AmiCal::Lexical_analyzer le_ana(_expr);
    switch (1) {
    case 1:
        if (!le_ana.pre_process()) break;
        AmiCal::Parser par_test(&le_ana);
        AmiCal::tree_node* target_tree;
        if (!(target_tree = par_test.get_parser_tree())) {
            break;
        }
        double result = calcu_tree_value(target_tree);
        return result;
    }
    return nan;
}

AMIC_NAMESPACE_END