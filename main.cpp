#include <iostream>
#include "donk.h"


int main() {
    Lab2 lab;
<<<<<<< HEAD
    double result = lab.FuncA();
=======
    int n;
    double x;
    std::cout << "Enter the value of x (in radians): ";
    std::cin >> x;
    std::cout << "Enter the number of terms in the series: ";
    std::cin >> n;
    double result = lab.FuncA(x, n);
>>>>>>> branchA
    std::cout << result << std::endl;
    return 0;
}
