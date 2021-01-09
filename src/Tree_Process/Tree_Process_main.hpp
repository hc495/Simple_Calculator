# pragma once
# include "../Parser/Parser_production.hpp"

AMIC_NAMESPACE_START

double calcu_tree_value(T_node::tree_node* root) { 
    try {
        return root->value();
    } catch (...) {
        std::cout << "(Ami003) Math error.\n";
        throw;
    }
}

AMIC_NAMESPACE_END