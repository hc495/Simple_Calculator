# include "../Parser/Parser_main.h"

int main() {
    std::string buf = "1 + 2";
    AmiCal::Lexical_analyzer test(buf);
    AmiCal::tree_node* res;
    test.pre_process();
    switch (1) {
    case 1:
        AmiCal::Parser par_test(&test);
        if (!(res = par_test.get_parser_tree())) {
            break;
        }
        std::cout << res->value();
    }
    return 0;
}