#include <iostream>
#include <sys/wait.h>
#include "donk.h"

extern void CreateHTTPserver();

void sigchldHandler(int s) {
    printf("Caught signal SIGCHLD\n");

    pid_t pid;
    int status;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status)) {
	    printf("\nChild process terminated");
	}
    }
}

void sigintHandler(int s) {
    printf("Caught signal %d. Starting graceful exit procedure", s);

    pid_t pid;
    int status;

    while ((pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            printf("\nChild process terminated");
        }
    }
    if (pid == -1) printf("\nAll child processes terminated");
    exit(EXIT_SUCCESS);
}

int main() {
    signal(SIGCHLD, sigchldHandler);
    signal(SIGINT, sigintHandler);
    
    Lab2 lab;
    int n;
    double x;
    std::cout << "Enter the value of x (in radians): ";
    std::cin >> x;
    std::cout << "Enter the number of terms in the series: ";
    std::cin >> n;
    double result = lab.FuncA(x, n);
    std::cout << result << std::endl;
    CreateHTTPserver();
    return 0;
}
