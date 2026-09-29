#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

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

int main(int argc, char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first_term> <common_ratio> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    errno = 0;
    long val = strtol(argv[3], &endptr, 10);
    if (errno != 0 || endptr == argv[3] || *endptr != '\0' || val <= 0 || val > 2147483647) {
        fprintf(stderr, "Error: n must be a positive integer\n");
        return EXIT_FAILURE;
    }
    int n = (int)val;
    errno = 0;
    double a = strtod(argv[1], &endptr);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: invalid first term\n");
        return EXIT_FAILURE;
    }
    errno = 0;
    double r = strtod(argv[2], &endptr);
    if (errno != 0 || endptr == argv[2] || *endptr != '\0') {
        fprintf(stderr, "Error: invalid common ratio\n");
        return EXIT_FAILURE;
    }
    double term = geometric_term(a, r, n);
    printf("%f\n", term);
    return EXIT_SUCCESS;
}