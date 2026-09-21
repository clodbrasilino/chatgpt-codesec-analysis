#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

#define INPUT_BUFFER_SIZE 64
#define MAX_ALLOWED_VALUE 1000000
#define MIN_ALLOWED_VALUE 1

uint64_t sum_fourth_power_even(int n) {
    uint64_t sum = 0;
    for (int i = 1; i <= n; i++) {
        uint64_t even = 2ULL * i;
        uint64_t square = even * even;
        uint64_t fourth = square * square;
        if (sum > UINT64_MAX - fourth) {
            return UINT64_MAX;
        }
        sum += fourth;
    }
    return sum;
}

static void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static int validate_and_parse_input(const char *input, size_t input_len, long *out_val) {
    if (input_len == 0 || input[0] == '\0') {
        return 0;
    }

    char *endptr;
    errno = 0;
    long val = strtol(input, &endptr, 10);

    if (errno != 0 || endptr == input) {
        return 0;
    }

    while (*endptr == ' ' || *endptr == '\t') {
        endptr++;
    }

    if (*endptr != '\n' && *endptr != '\0') {
        return 0;
    }

    if (val < MIN_ALLOWED_VALUE || val > MAX_ALLOWED_VALUE) {
        return 0;
    }

    *out_val = val;
    return 1;
}

int main(void) {
    char input[INPUT_BUFFER_SIZE] = {0};

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    size_t len = strnlen(input, sizeof(input));
    if (len >= sizeof(input)) {
        len = sizeof(input) - 1;
    }

    int has_newline = 0;
    if (len > 0 && input[len - 1] == '\n') {
        has_newline = 1;
    }

    if (len == 0 || (len == sizeof(input) - 1 && !has_newline)) {
        if (len > 0) {
            clear_input_buffer();
        }
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    long val;
    if (!validate_and_parse_input(input, len, &val)) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    int n = (int)val;
    uint64_t result = sum_fourth_power_even(n);
    if (result == UINT64_MAX) {
        fprintf(stderr, "Overflow detected.\n");
        return EXIT_FAILURE;
    }
    printf("%" PRIu64 "\n", result);

    return EXIT_SUCCESS;
}