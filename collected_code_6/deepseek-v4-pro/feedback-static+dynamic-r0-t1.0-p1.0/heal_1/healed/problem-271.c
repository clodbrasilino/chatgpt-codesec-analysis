#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

long long sum_fifth_power_even(int n) {
    if (n < 0) {
        return 0;
    }
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        long long even = 2LL * i;
        if (even > 0 && even > LLONG_MAX / even) {
            return -1;
        }
        long long square = even * even;
        if (square > 0 && even > LLONG_MAX / square) {
            return -1;
        }
        long long cube = square * even;
        if (cube > 0 && square > LLONG_MAX / cube) {
            return -1;
        }
        long long fourth = cube * even;
        if (fourth > 0 && cube > LLONG_MAX / fourth) {
            return -1;
        }
        long long term = fourth * even;
        if (term > 0 && fourth > LLONG_MAX / term) {
            return -1;
        }
        if (sum > 0 && term > LLONG_MAX - sum) {
            return -1;
        }
        sum += term;
    }
    return sum;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }
    if (n < 0) {
        printf("n must be non-negative.\n");
        return EXIT_FAILURE;
    }
    long long result = sum_fifth_power_even(n);
    if (result == -1) {
        printf("Overflow occurred during computation.\n");
        return EXIT_FAILURE;
    }
    printf("Sum of fifth powers of first %d even natural numbers: %lld\n", n, result);
    return EXIT_SUCCESS;
}