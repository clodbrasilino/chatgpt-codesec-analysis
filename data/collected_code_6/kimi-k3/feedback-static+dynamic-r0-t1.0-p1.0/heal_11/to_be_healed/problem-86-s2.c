#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>

int64_t centered_hexagonal(int64_t n) {
    if (n < 1 || n > 1290166) {
        return -1;
    }
    return 3 * n * (n - 1) + 1;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *endptr;
    long val;
    int64_t n;
    int64_t result;
    size_t len;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(input, sizeof(input));

    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (input[len - 1] != '\n') {
        if (len == sizeof(input) - 1) {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            fprintf(stderr, "Input too long\n");
            return EXIT_FAILURE;
        }
    } else {
        input[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(input, &endptr, 10);

    if (errno != 0 || endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (val < 1 || val > 1290166) {
        fprintf(stderr, "Input out of valid range\n");
        return EXIT_FAILURE;
    }

    n = (int64_t)val;
    result = centered_hexagonal(n);

    if (result < 0) {
        fprintf(stderr, "Calculation error\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", (long long)result);
    return EXIT_SUCCESS;
}