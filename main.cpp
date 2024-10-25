#include <iostream>
#include "donk.h"


int main() {
    Lab2 lab;
    int n;
    std::cout << "Enter the number of terms in the series: ";
    std::cin >> n;
    double result = lab.FuncA(n);
    std::cout << result << std::endl;
    return 0;
}
