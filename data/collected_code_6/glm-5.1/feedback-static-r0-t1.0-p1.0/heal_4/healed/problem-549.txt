#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long sum_fifth_power_odd(int n) {
    if (n < 0) {
        return 0;
    }

    unsigned long long sum = 0;
    int count = 0;
    int current = 1;

    while (count < n) {
        unsigned long long term = (unsigned long long)current * current * current * current * current;
        sum += term;
        current += 2;
        count++;
    }

    return sum;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val < 0 || val > INT_MAX) {
        fprintf(stderr, "Invalid input: n must be a valid non-negative integer\n");
        return EXIT_FAILURE;
    }

    int bound_checked_val = (int)val;

    unsigned long long result = sum_fifth_power_odd(bound_checked_val);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}