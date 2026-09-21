#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main(int argc, char *argv[]) {
    int n;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t len = strnlen(argv[1], 12);
    if (len == 0 || len > 11) {
        fprintf(stderr, "Invalid input: integer out of range or improperly restricted\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buf[12];
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buf, argv[1], len);
    buf[len] = '\0';

    char *endptr;
    long val = strtol(buf, &endptr, 10);
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