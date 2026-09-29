#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t binomial_coefficient(int n, int k) {
    if (k > n - k) k = n - k;
    uint64_t res = 1;
    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

uint64_t sum_even_index_binomial_coefficients(int n) {
    uint64_t sum = 0;
    for (int i = 0; i <= n; i += 2) {
        sum += binomial_coefficient(n, i);
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a value for n: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    uint64_t result = sum_even_index_binomial_coefficients(n);
    /* Possible weaknesses found:
     *  %llu in format string (no. 1) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     */
    printf("Sum of even index binomial coefficients: %llu\n", result);
    return EXIT_SUCCESS;
}