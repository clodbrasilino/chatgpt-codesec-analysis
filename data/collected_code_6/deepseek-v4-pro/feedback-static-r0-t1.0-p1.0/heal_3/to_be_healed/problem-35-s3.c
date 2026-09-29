#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>

unsigned long long rectangular_number(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: n must be non-negative\n");
        exit(EXIT_FAILURE);
    }
    return (unsigned long long)n * (n + 1);
}

int main(void) {
    int n;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[32];
    size_t len;

    printf("Enter n: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read input\n");
        return EXIT_FAILURE;
    }

    len = 0;
    while (input[len] != '\0') {
        len++;
    }
    if (len > 0 && input[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) { }
        fprintf(stderr, "Error: Input too long\n");
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long val = strtol(input, &endptr, 10);

    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Error: n out of range\n");
        return EXIT_FAILURE;
    }

    if (endptr == input) {
        fprintf(stderr, "Error: Invalid integer input\n");
        return EXIT_FAILURE;
    }

    while (*endptr != '\0') {
        if (*endptr != ' ' && *endptr != '\t' && *endptr != '\n' && *endptr != '\r') {
            fprintf(stderr, "Error: Invalid integer input\n");
            return EXIT_FAILURE;
        }
        endptr++;
    }

    if (val < 0) {
        fprintf(stderr, "Error: n out of range\n");
        return EXIT_FAILURE;
    }

    n = (int)val;

    unsigned long long result = rectangular_number(n);
    printf("The %d-th rectangular number is %llu\n", n, result);

    return EXIT_SUCCESS;
}