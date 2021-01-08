# pragma once
# include "../Parser/Parser_main.hpp"

AMIC_NAMESPACE_START

double calcu_tree_value(tree_node* root) { 
    try {
        return root->value();
    } catch (...) {
        std::cout << "Math error.\n";
        return nan(0);
    }
}

AMIC_NAMESPACE_END