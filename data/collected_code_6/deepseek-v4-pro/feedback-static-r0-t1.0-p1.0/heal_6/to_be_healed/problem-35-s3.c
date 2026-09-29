#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

unsigned long long rectangular_number(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: n must be non-negative\n");
        exit(EXIT_FAILURE);
    }
    if (n > INT_MAX - 1) {
        fprintf(stderr, "Error: overflow in calculation\n");
        exit(EXIT_FAILURE);
    }
    return (unsigned long long)n * (unsigned long long)(n + 1);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[32];
    size_t len;
    long val;
    char *endptr;
    int n;
    unsigned long long result;

    printf("Enter n: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(input, sizeof(input));
    if (len == 0) {
        fprintf(stderr, "Error: Invalid integer input\n");
        return EXIT_FAILURE;
    }

    if (input[len - 1] != '\n') {
        if (len == sizeof(input) - 1) {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) { }
            fprintf(stderr, "Error: Input too long\n");
            return EXIT_FAILURE;
        }
    } else {
        input[len - 1] = '\0';
    }

    errno = 0;
    val = strtol(input, &endptr, 10);

    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Error: n out of range\n");
        return EXIT_FAILURE;
    }

    if (endptr == input) {
        fprintf(stderr, "Error: Invalid integer input\n");
        return EXIT_FAILURE;
    }

    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            fprintf(stderr, "Error: Invalid integer input\n");
            return EXIT_FAILURE;
        }
        endptr++;
    }

    if (val < 0) {
        fprintf(stderr, "Error: n must be non-negative\n");
        return EXIT_FAILURE;
    }

    n = (int)val;
    result = rectangular_number(n);
    printf("The %d-th rectangular number is %llu\n", n, result);

    return EXIT_SUCCESS;
}