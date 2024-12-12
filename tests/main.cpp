#include <iostream>
#include <cmath>
#include "../donk.h"

int main(int argc, char* argv[]) {
	Lab2 lab;
	double result = lab.FuncA(1, 100);
	double dif = std::fabs(std::tan(1) - result);
	if (dif < 1e-4) {
		return 0;
	}
	return 1;
}
