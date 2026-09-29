#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

double geometric_term(double a, double r, int n) {
    if (n <= 0) {
        return 0.0;
    }
    double result = 1.0;
    int exp = n - 1;
    double base = r;
    if (base < 0 && exp % 2 != 0) {
        base = -base;
        result = -1.0;
    } else if (base < 0) {
        base = -base;
        result = 1.0;
    }
    while (exp > 0) {
        if (exp % 2 == 1) {
            result *= base;
        }
        base *= base;
        exp /= 2;
    }
    return a * result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first_term> <common_ratio> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    double a = atof(argv[1]);
    double r = atof(argv[2]);
    long n_long = strtol(argv[3], NULL, 10);
    if (n_long <= 0 || n_long > INT_MAX) {
        fprintf(stderr, "Error: n must be a positive integer\n");
        return EXIT_FAILURE;
    }
    int n = (int)n_long;
    double term = geometric_term(a, r, n);
    printf("%f\n", term);
    return EXIT_SUCCESS;
}