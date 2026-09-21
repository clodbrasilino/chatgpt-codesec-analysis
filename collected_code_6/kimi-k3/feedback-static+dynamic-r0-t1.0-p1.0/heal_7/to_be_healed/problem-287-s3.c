#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

unsigned long long sum_of_squares_even(int n)
{
    unsigned long long sum = 0;
    int i;

    for (i = 1; i <= n; i++) {
        unsigned long long even = (unsigned long long)i * 2;
        sum += even * even;
    }

    return sum;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    char *endptr;
    long value;
    int n;
    size_t len;
    int truncated = 0;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(input, sizeof(input));
    if (len == sizeof(input) && !feof(stdin)) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        truncated = 1;
    } else if (len > 0 && input[len - 1] != '\n' && !feof(stdin)) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        truncated = 1;
    }

    if (truncated) {
        fprintf(stderr, "Invalid input: input too long\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtol(input, &endptr, 10);

    if (errno == ERANGE || value > INT_MAX || value < 0) {
        fprintf(stderr, "Invalid input: out of range\n");
        return EXIT_FAILURE;
    }

    if (endptr == input) {
        fprintf(stderr, "Invalid input: not a number\n");
        return EXIT_FAILURE;
    }

    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n' || *endptr == '\r') {
        endptr++;
    }

    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input: trailing characters\n");
        return EXIT_FAILURE;
    }

    n = (int)value;
    printf("%llu\n", sum_of_squares_even(n));

    return EXIT_SUCCESS;
}