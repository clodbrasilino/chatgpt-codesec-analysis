#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t sum_fifth_power_even(int n) {
    if (n <= 0) {
        return 0;
    }
    uint64_t sum = 0;
    for (int i = 1; i <= n; i++) {
        uint64_t even = 2ULL * i;
        uint64_t square = even * even;
        uint64_t fourth = square * square;
        uint64_t fifth = fourth * even;
        if (fifth / even != fourth) {
            fprintf(stderr, "Overflow detected at i=%d\n", i);
            return 0;
        }
        uint64_t new_sum = sum + fifth;
        if (new_sum < sum) {
            fprintf(stderr, "Overflow detected in accumulation at i=%d\n", i);
            return 0;
        }
        sum = new_sum;
    }
    return sum;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return EXIT_FAILURE;
    }
    printf("Sum of fifth powers of first %d even natural numbers: %" PRIu64 "\n", n, sum_fifth_power_even(n));
    return EXIT_SUCCESS;
}