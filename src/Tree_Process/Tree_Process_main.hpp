# pragma once
# include "../Parser/Parser_main.hpp"

AMIC_NAMESPACE_START

constexpr double nan = 0xFFF8000000000000;

double calcu_tree_value(tree_node* root) { 
    try {
        return root->value();
    } catch (...) {
        std::cout << "Math error.\n";
        return nan;
    }
}

AMIC_NAMESPACE_END