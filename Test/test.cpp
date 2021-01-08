# include "../src/AMI_Calcu.hpp"

double first(const std::vector<double> &a) {
    return a.front();
}

int main() {
    AmiCal::insert_function("sum", first);
    AmiCal::insert_macro("ad", "sum");
    std::cout << AmiCal::etod("-(-(-1.234))*$ad$$e$$e$+2/ $123");
    return 0;
}