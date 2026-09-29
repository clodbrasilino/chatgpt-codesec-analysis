#include <stdio.h>
#include <stdlib.h>

double harmonic_sum(int n) {
    if (n < 1) {
        return 0.0;
    }
    double sum = 0.0;
    for (int i = 1; i < n; i++) {
        sum += 1.0 / i;
    }
    return sum;
}

int main(int argc, char *argv[]) {
    int n = 0;
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    n = atoi(argv[1]);
    if (n < 1) {
        return EXIT_FAILURE;
    }
    double result = harmonic_sum(n);
    printf("%.15f\n", result);
    return EXIT_SUCCESS;
}