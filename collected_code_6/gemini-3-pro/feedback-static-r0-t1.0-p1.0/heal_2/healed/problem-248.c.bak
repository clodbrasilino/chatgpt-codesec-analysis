#include <stdio.h>
#include <stdlib.h>

double harmonic_sum_n_minus_one(int n) {
    if (n <= 1) {
        return 0.0;
    }

    double sum = 0.0;
    for (int i = 1; i < n; i++) {
        sum += 1.0 / (double)i;
    }

    return sum;
}

int main(int argc, const char *argv[]) {
    int n = 5;
    
    if (argc > 1) {
        n = atoi(argv[1]);
    }

    if (n > 1) {
        double result = harmonic_sum_n_minus_one(n);
        printf("%.6f\n", result);
    } else {
        printf("0.000000\n");
    }

    return EXIT_SUCCESS;
}