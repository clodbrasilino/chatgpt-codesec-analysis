#include <stdio.h>

double geometric_nth_term(double a, double r, unsigned int n) {
    return a * pow(r, n - 1);
}

int main() {
    double a = 1.0;
    double r = 2.0;
    unsigned int n = 10;
    
    double result = geometric_nth_term(a, r, n);
    printf("The %uth term of the geometric series is: %f\n", n, result);
    return 0;
}