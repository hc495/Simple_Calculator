# include "../AMI_Calcu.hpp"

double first(const std::vector<double> &a) {
    return a.front();
}

int main() {
    AmiCal::insert_function("sum", first);
    AmiCal::insert_macro("ad", "sum");
    std::string test = "1+2+3+pow(1)";
    std::cout << AmiCal::etod(test);
    return 0;
}