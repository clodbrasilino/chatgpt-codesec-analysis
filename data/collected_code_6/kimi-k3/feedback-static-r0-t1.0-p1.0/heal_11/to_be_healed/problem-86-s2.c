#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 128
#define MAX_HEXAGONAL_N 1290

long long centered_hexagonal(int n) {
    if (n < 1) {
        return -1;
    }
    return (long long)n * n * n - (long long)(n - 1) * (n - 1) * (n - 1);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_SIZE];
    char *endptr;
    long val;
    int n;
    long long result;
    size_t len;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(input, sizeof(input));
    if (len == sizeof(input)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else if (len == sizeof(input) - 1 && input[len - 1] != '\n') {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(input, &endptr, 10);

    if (errno != 0 || endptr == input) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
        endptr++;
    }

    if (val < 1 || val > MAX_HEXAGONAL_N) {
        fprintf(stderr, "Input out of valid range\n");
        return EXIT_FAILURE;
    }

    n = (int)val;
    result = centered_hexagonal(n);

    if (result < 0) {
        fprintf(stderr, "Calculation error\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);
    return EXIT_SUCCESS;
}