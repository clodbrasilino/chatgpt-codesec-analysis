#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long sum_of_fourth_powers(int n) {
    if (n < 0) {
        return 0;
    }

    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        if (i > USHRT_MAX) {
            errno = ERANGE;
            return 0;
        }
        unsigned long long term = (unsigned long long)i * i;
        if (term > ULLONG_MAX / term) {
            errno = ERANGE;
            return 0;
        }
        unsigned long long fourth_power = term * term;
        if (fourth_power > ULLONG_MAX - sum) {
            errno = ERANGE;
            return 0;
        }
        sum += fourth_power;
    }

    return sum;
}

int main(int argc, char *argv[]) {
    int n;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (errno == ERANGE || *endptr != '\0' || val < 0 || val > INT_MAX) {
        fprintf(stderr, "Invalid input: must be a non-negative integer within int range\n");
        return EXIT_FAILURE;
    }
    n = (int)val;

    unsigned long long result = sum_of_fourth_powers(n);
    if (errno == ERANGE) {
        fprintf(stderr, "Overflow error: n is too large\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", result);
    return EXIT_SUCCESS;
}