#ifndef DONK_H
#define DONK_H

#include <iostream>
#include <unordered_map>
#include <cmath>
#include <vector>


class Lab2 {
public: 
    double FuncA(int n) {
        double x;

        std::cout << "Enter the value of x (in radians): ";
        std::cin >> x;
        
        return taylorTan(x, n);
    };

private:        
    std::unordered_map<int, double> bernoulliCache;
    std::unordered_map<std::string, int> binomialCache;
    std::vector<double> factorialCache = {1, 1};
    
    double taylorTan(double x, int terms) {
        x = std::fmod(x, M_PI);
        if (x > M_PI / 2) x -= M_PI;
        else if (x < -M_PI / 2) x += M_PI;

        double sum = 0.0;

        for (int n = 0; n < terms; n++) {
            double term = getBernoulliNumber(2 * n) * std::pow(-4, n)
            * (1 - std::pow(4, n)) * std::pow(x, 2 * n - 1) / getFactorial(2 * n);

            if (std::isinf(term) || std::isnan(term)) {
                std::cout << term << "-err" << std::endl;
                break;
            }

            sum += term;
        }

        return sum;
    };

    std::vector<double> bernoulliNumbers(int n) {
        std::vector<double> B(n + 1, 0.0);
        B[0] = 1.0;

        for (int m = 1; m <= n; m++) {
            B[m] = 0.0;
            for (int j = 0; j < m; j++) {
                B[m] -= (B[j] * getBinomialCoefficient(m + 1, j)) / (m + 1);
            }
        }
        return B;
    };

    double getBernoulliNumber(int n) {
        if (bernoulliCache.find(n) != bernoulliCache.end()) {
            return bernoulliCache[n];
        }
        std::vector<double> B = bernoulliNumbers(n);
        bernoulliCache[n] = B[n];
        return B[n];
    };

    int getBinomialCoefficient(int n, int k) {
        std::string key = std::to_string(n) + "," + std::to_string(k);
        if (binomialCache.find(key) != binomialCache.end()) {
            return binomialCache[key];
        }

        if (k > n) return 0;
        if (k == 0 || k == n) return 1;

        int res = 1;
        for (int i = 0; i < k; i++) {
            res = res * (n - i) / (i + 1);
        }
        binomialCache[key] = res;
        return res;
    };

    double getFactorial(int n) {
        while (n >= factorialCache.size()) {
            int nextIndex = factorialCache.size();
            factorialCache.push_back(factorialCache[nextIndex - 1] * nextIndex);
        }
        return factorialCache[n];
    };
};
#endif
