#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>

int64_t nth_rectangular_number(int64_t n) {
    if (n > INT64_MAX / (n + 1)) {
        fprintf(stderr, "Overflow detected\n");
        return -1;
    }
    int64_t result = n * (n + 1);
    return result;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[20];
    printf("Enter the value of n: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    char *endptr;
    errno = 0;
    int64_t n = strtoll(input, &endptr, 10);

    if (errno != 0 || *endptr != '\n' && *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (n < 1 || n > INT64_MAX) {
        fprintf(stderr, "n must be a positive integer within range\n");
        return 1;
    }

    int64_t result = nth_rectangular_number(n);
    if (result == -1) {
        return 1;
    }

    printf("The %" PRId64 "-th rectangular number is: %" PRId64 "\n", n, result);
    return 0;
}