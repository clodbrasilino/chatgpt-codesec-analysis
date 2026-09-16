#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

unsigned long long calculate_difference(unsigned int n) {
    unsigned long long sum_n = (unsigned long long)n * (n + 1) / 2;
    unsigned long long sum_sq_n = (unsigned long long)n * (n + 1) * (2ULL * n + 1) / 6;

    if (sum_n * sum_n > ULLONG_MAX) {
        exit(EXIT_FAILURE);
    }

    unsigned long long squared_sum = sum_n * sum_n;

    if (squared_sum < sum_sq_n) {
        exit(EXIT_FAILURE);
    }

    return squared_sum - sum_sq_n;
}

int main(void) {
    unsigned int n = 10;
    unsigned long long result = calculate_difference(n);
    printf("%llu\n", result);
    return 0;
}