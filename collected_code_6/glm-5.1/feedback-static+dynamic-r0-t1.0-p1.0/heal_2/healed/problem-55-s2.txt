#include <stdio.h>
#include <stdlib.h>

double geometric_term(double a, double r, int n) {
    if (n <= 0) {
        return 0.0;
    }
    double result = 1.0;
    int exp = n - 1;
    double base = r;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result *= base;
        }
        base *= base;
        exp /= 2;
    }
    return a * result;
}

int main(int argc, char * const argv[const]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first_term> <common_ratio> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    double a = atof(argv[1]);
    double r = atof(argv[2]);
    int n = atoi(argv[3]);
    if (n <= 0) {
        fprintf(stderr, "Error: n must be a positive integer\n");
        return EXIT_FAILURE;
    }
    double term = geometric_term(a, r, n);
    printf("%f\n", term);
    return EXIT_SUCCESS;
}