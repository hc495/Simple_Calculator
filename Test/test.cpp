# include "../src/AMI_Calcu.hpp"

double first(const std::vector<double> &a) {
    return a.front();
}

int main() {
    AmiCal::insert_function("sum", first);
    AmiCal::insert_macro("ad", "sum");
    std::cout << AmiCal::get_error_code("-1--1");
    return 0;
}