# include "../AMI_Calcu.hpp"

int main() {
    std::string test = "1+2+3+6*(5+1)";
    std::cout << AmiCal::etod(test);
    return 0;
}