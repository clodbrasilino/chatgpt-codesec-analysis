#include <stdio.h>
#include <stdlib.h>

unsigned long long binomial_coefficient(int n, int k) {
    if (k < 0 || n < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    if (k > n - k) k = n - k;
    unsigned long long res = 1;
    for (int i = 0; i < k; i++) {
        if (res > (unsigned long long)-1 / (n - i)) return 0;
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

unsigned long long sum_of_product_binomial(int n, int k) {
    unsigned long long sum = 0;
    for (int i = 0; i <= k; i++) {
        unsigned long long b1 = binomial_coefficient(n, i);
        unsigned long long b2 = binomial_coefficient(n, k - i);
        if (b1 == 0 || b2 == 0) return 0;
        if (b1 > (unsigned long long)-1 / b2) return 0;
        unsigned long long product = b1 * b2;
        if (sum > (unsigned long long)-1 - product) return 0;
        sum += product;
    }
    return sum;
}

int main(int argc, char const * const * argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr1, *endptr2;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);
    if (*endptr1 != '\0' || *endptr2 != '\0' || val1 < 0 || val2 < 0) {
        fprintf(stderr, "Error: n and k must be non-negative integers.\n");
        return EXIT_FAILURE;
    }
    unsigned long long result = sum_of_product_binomial((int)val1, (int)val2);
    if (result == 0 && (val1 > 0 || val2 > 0)) {
        fprintf(stderr, "Error: Arithmetic overflow detected.\n");
        return EXIT_FAILURE;
    }
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}