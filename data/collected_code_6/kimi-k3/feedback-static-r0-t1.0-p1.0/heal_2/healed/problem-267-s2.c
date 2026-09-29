#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_INPUT_LEN 64
#define MAX_N 2642245ULL

uint64_t sum_of_squares_of_first_n_odd(uint64_t n) {
    if (n > MAX_N) {
        return UINT64_MAX;
    }
    return n * (2 * n + 1) * (2 * n - 1) / 3;
}

int main(void) {
    char input[MAX_INPUT_LEN];
    char *endptr;
    unsigned long long temp;
    uint64_t n;
    uint64_t result;
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
    if (len > 0 && input[len - 1] != '\n' && !feof(stdin)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    temp = strtoull(input, &endptr, 10);

    if (errno == ERANGE || endptr == input || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (temp > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    n = (uint64_t)temp;

    result = sum_of_squares_of_first_n_odd(n);

    if (result == UINT64_MAX && n != 0) {
        fprintf(stderr, "Result would overflow\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);

    return EXIT_SUCCESS;
}