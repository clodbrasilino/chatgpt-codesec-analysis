#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double ln_lobb_number(int n, int m) {
    if (n <= 0 || m <= 0 || m > n) {
        return NAN;
    }
    double num_1 = tgamma(2 * n + 1);
    double den_1 = tgamma(n + 1);
    double term_1 = num_1 / (den_1 * den_1);
    double num_2 = tgamma(2 * m + 1);
    double double_den_2 = tgamma(m + 1);
    double term_2 = num_2 / (double_den_2 * double_den_2);
    double num_3 = tgamma(2 * (n - m) + 1);
    double double_den_3 = tgamma((n - m) + 1);
    double term_3 = num_3 / (double_den_3 * double_den_3);
    if (term_2 <= 0 || term_3 <= 0) {
        return NAN;
    }
    return log(term_1 * (term_2 * term_3));
}

int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    double result = ln_lobb_number(n, m);
    if (isnan(result)) {
        return EXIT_FAILURE;
    }
    printf("%.15e\n", result);
    return EXIT_SUCCESS;
}