#include <stdio.h>
#include <limits.h>

long long calculate_difference(unsigned int n) {
    if (n > 2097151U) {
        return -1;
    }

    unsigned long long sum = (unsigned long long)n * (n + 1) / 2;
    if (sum > (unsigned long long)LLONG_MAX) return -1;

    unsigned long long squared_sum = sum * sum;
    if (squared_sum > (unsigned long long)LLONG_MAX) return -1;

    unsigned long long sum_of_squares = (unsigned long long)n * (n + 1) / 2 * (2ULL * n + 1) / 3;
    if (sum_of_squares > (unsigned long long)LLONG_MAX) return -1;

    if (squared_sum > (unsigned long long)LLONG_MAX - sum_of_squares) return -1;

    long long s_sq = (long long)squared_sum;
    long long so_sq = (long long)sum_of_squares;

    return s_sq - so_sq;
}

int main(void) {
    unsigned int n;

    if (scanf("%u", &n) != 1) {
        return 1;
    }

    long long result = calculate_difference(n);

    if (result == -1) {
        return 1;
    }

    printf("%lld\n", result);
    return 0;
}