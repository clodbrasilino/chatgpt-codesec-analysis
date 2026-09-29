#include <stdio.h>
#include <stdlib.h>

long long sum_even_index_binomial_coefficients(int n) {
    long long sum = 0;
    long long c = 1;
    int i;
    for (i = 0; i <= n; i++) {
        if (i % 2 == 0) {
            sum += c;
        }
        if (i < n) {
            c = c * (n - i) / (i + 1);
        }
    }
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > 62) {
        return EXIT_FAILURE;
    }
    int n = (int)val;
    long long result = sum_even_index_binomial_coefficients(n);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}