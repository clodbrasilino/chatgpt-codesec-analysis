#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>

uint64_t sum_of_squares_of_first_n_odd(uint64_t n) {
    if (n > 2642245) {
        return UINT64_MAX;
    }
    return n * (2 * n + 1) * (2 * n - 1) / 3;
}

int main(void) {
    char input[64];
    char *endptr;
    uint64_t n;
    uint64_t result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoull(input, &endptr, 10);

    if (errno != 0 || endptr == input || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = sum_of_squares_of_first_n_odd(n);

    if (result == UINT64_MAX && n != 0) {
        fprintf(stderr, "Result would overflow\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);

    return EXIT_SUCCESS;
}