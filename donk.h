#ifndef DONK_H
#define DONK_H

#include <iostream>
#include <unordered_map>
#include <cmath>
#include <vector>


class Lab2 {
/**
 * Class representing mathematical operations.
 */
public: 
    /**
      * Returns value of Taylor series approximation for tan(x).
      * 
      * @param x The angle in radians for which to compute tan(x).
      * @param n The number of terms to include in the Taylor series approximation.
      * @return taylorTan(x, n).
      */
    double FuncA(int x, n) {      
        return taylorTan(x, n);
    };

private:
    // Maps and vector to cache used values
    std::unordered_map<int, double> bernoulliCache; 
    std::unordered_map<std::string, int> binomialCache;
    std::vector<double> factorialCache = {1, 1};
    
    /**
      * Implementation of Taylor series approximation for tan(x)
      * 
      * @param x The angle in radians for which to compute tan(x). Value is adjusted to be in range [0;Pi/2]
      * @param n The number of terms to include in the Taylor series approximation.
      * @return The approximate value of tan(x) computed using the specified number of terms.
      */
    double taylorTan(double x, int terms) {
        x = std::fmod(x, M_PI);
        if (x > M_PI / 2) x -= M_PI;
        else if (x < -M_PI / 2) x += M_PI;

        double sum = 0.0;

        for (int n = 0; n < terms; n++) {            
            double term = getBernoulliNumber(2 * n) * std::pow(-4, n)
            * (1 - std::pow(4, n)) * std::pow(x, 2 * n - 1) / getFactorial(2 * n);

            if (std::isinf(term) || std::isnan(term)) {
                break;
            }

            sum += term;
        }

        return sum;
    };
    
    /**
      * Computes Bernoulli numbers up to B_n using a specific recursive formula.
      * 
      * @param n The maximum index of the Bernoulli numbers to compute.
      * @return A vector containing the computed Bernoulli numbers from B_0 to B_n.
      */
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

    /**
      * Retrieves the nth Bernoulli number, calculating it if not already cached.
      * 
      * @param n The index of the Bernoulli number to retrieve.
      * @return The nth Bernoulli number.
      */
    double getBernoulliNumber(int n) {
        if (bernoulliCache.find(n) != bernoulliCache.end()) {
            return bernoulliCache[n];
        }
        std::vector<double> B = bernoulliNumbers(n);
        bernoulliCache[n] = B[n];
        return B[n];
    };
    
    /**
      * Computes the binomial coefficient C(n, k) = n! / (k! * (n - k)!).
      * 
      * @param n The total number of items.
      * @param k The number of items to choose.
      * @return The binomial coefficient C(n, k).
      */
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
    
    /**
      * Computes the factorial of n, caching results to improve efficiency.
      * 
      * @param n The number for which to compute the factorial.
      * @return The factorial of n (n!).
      */
    double getFactorial(int n) {
        while (n >= factorialCache.size()) {
            int nextIndex = factorialCache.size();
            factorialCache.push_back(factorialCache[nextIndex - 1] * nextIndex);
        }
        return factorialCache[n];
    };
};
#endif
