#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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

int main(int argc, char * const argv[]) {
    int n;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t len = strlen(argv[1]);
    if (len == 0 || len > 10) {
        fprintf(stderr, "Invalid input: integer out of range or improperly restricted\n");
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || errno == ERANGE) {
        fprintf(stderr, "Invalid input: not a valid integer\n");
        return EXIT_FAILURE;
    }

    if (val < 0 || val > INT_MAX) {
        fprintf(stderr, "Invalid input: n must be a non-negative integer within int range\n");
        return EXIT_FAILURE;
    }

    n = (int)val;

    unsigned long long result = sum_fifth_power_odd(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}