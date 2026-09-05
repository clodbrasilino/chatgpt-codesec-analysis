#include <stdio.h>
#include <stdlib.h>

long long sum_even_index_binomial_coefficients(int n) {
    long long sum = 0;
    long long c = 1;
    for (int i = 0; i <= n; i++) {
        if (i % 2 == 0) {
            sum += c;
        }
        if (i < n) {
            c = c * (n - i) / (i + 1);
        }
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
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