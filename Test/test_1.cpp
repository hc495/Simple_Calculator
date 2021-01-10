# include "../src/AMI_Calcu.hpp"

double first(const std::vector<double> &a) {
    return a.front();
}

int main() {
    AmiCal::insert_function("sum_22", first);
    AmiCal::insert_macro("ad", "sum");
    return 0;
}