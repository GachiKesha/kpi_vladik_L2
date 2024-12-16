#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>
#include <random>
#include "../donk.h"

int main(int argc, char* argv[]) {
    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<int> aValues;
    std::mt19937 mtre {123};
    std::uniform_real_distribution<double> distr {-50.0, 50.0};
    std::uniform_int_distribution<int> terms {10, 1000};
    Lab2 lab;			
    for (int i=0; i<200000; i++) {
        aValues.push_back(lab.FuncA(distr(mtre), terms(mtre)));
    }		
    for (int i=0; i<100; i++) {
        sort(begin(aValues), end(aValues));
        reverse(begin(aValues), end(aValues));
    }	
    auto t2 = std::chrono::high_resolution_clock::now();
    auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);

    int iMS = int_ms.count();
    std::cout << iMS << std::endl;
    if (iMS < 20000) {
        return 0;
    }
    return 1;
}

