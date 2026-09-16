#include <stdio.h>
#include <stdlib.h>

unsigned long long binomial_coefficient(unsigned int n, unsigned int k) {
    unsigned long long res = 1;
    if (k > n - k) {
        k = n - k;
    }
    for (unsigned int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

unsigned long long catalan_number(unsigned int n) {
    if (n == 0) {
        return 1;
    }
    return binomial_coefficient(2 * n, n) / (n + 1);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0' || val > 34) {
        fprintf(stderr, "Error: n must be a non-negative integer <= 34\n");
        return EXIT_FAILURE;
    }
    unsigned int n = (unsigned int)val;
    unsigned long long result = catalan_number(n);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}