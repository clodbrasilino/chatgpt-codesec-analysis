#include <stdio.h>
#include <stdlib.h>

double harmonic_sum_n_minus_1(int n) {
    if (n <= 1) {
        return 0.0;
    }

    double sum = 0.0;
    for (int i = 1; i < n; ++i) {
        sum += 1.0 / (double)i;
    }

    return sum;
}

int main(void) {
    int n = 0;

    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (n <= 1) {
        return EXIT_FAILURE;
    }

    double result = harmonic_sum_n_minus_1(n);
    printf("%f\n", result);

    return EXIT_SUCCESS;
}