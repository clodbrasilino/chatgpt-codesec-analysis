#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_one_less_than_twice_reverse(int64_t number)
{
    uint64_t value;
    uint64_t reversed = 0U;
    uint64_t original;

    if (number < 0) {
        return false;
    }

    value = (uint64_t)number;
    original = value;

    do {
        const uint64_t digit = value % 10U;

        if (reversed > (UINT64_MAX - digit) / 10U) {
            return false;
        }

        reversed = (reversed * 10U) + digit;
        value /= 10U;
    } while (value != 0U);

    if (reversed > UINT64_MAX / 2U) {
        return false;
    }

    return original + 1U == reversed * 2U;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    intmax_t parsed;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoimax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed < 0 || parsed > INT64_MAX) {
        fprintf(stderr, "Invalid number\n");
        return EXIT_FAILURE;
    }

    puts(is_one_less_than_twice_reverse((int64_t)parsed) ? "true" : "false");
    return EXIT_SUCCESS;
}