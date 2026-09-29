#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_one_less_than_twice_reverse(int64_t number)
{
    uint64_t value;
    uint64_t reversed = UINT64_C(0);
    uint64_t original;

    if (number < 0) {
        return false;
    }

    value = (uint64_t)number;
    original = value;

    do {
        const uint64_t digit = value % UINT64_C(10);

        if (reversed > (UINT64_MAX - digit) / UINT64_C(10)) {
            return false;
        }

        reversed = reversed * UINT64_C(10) + digit;
        value /= UINT64_C(10);
    } while (value != UINT64_C(0));

    if (reversed > UINT64_MAX / UINT64_C(2)) {
        return false;
    }

    return original + UINT64_C(1) == reversed * UINT64_C(2);
}

int main(int argc, const char *const argv[])
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
        fputs("Invalid number\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_one_less_than_twice_reverse((int64_t)parsed) ? "true" : "false");

    return EXIT_SUCCESS;
}