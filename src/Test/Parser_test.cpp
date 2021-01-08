# include "../AMI_Calcu.hpp"

int main() {
    std::string test = "1+2+3+sin()";
    std::cout << AmiCal::etod(test);
    return 0;
}