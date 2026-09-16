#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_palindrome(uint64_t value)
{
    uint64_t original = value;
    uint64_t reversed = 0;

    do {
        reversed = (reversed * 10U) + (value % 10U);
        value /= 10U;
    } while (value != 0U);

    return reversed == original;
}

static int previous_palindrome(uint64_t value, uint64_t *result)
{
    uint64_t candidate;

    if (result == NULL || value == 0U) {
        return 0;
    }

    candidate = value - 1U;

    for (;;) {
        if (is_palindrome(candidate)) {
            *result = candidate;
            return 1;
        }

        if (candidate == 0U) {
            return 0;
        }

        --candidate;
    }
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    if (argc != 2) {
        (void)fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || parsed > UINT64_MAX) {
        (void)fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!previous_palindrome((uint64_t)parsed, &result)) {
        (void)fprintf(stderr, "No previous non-negative palindrome exists\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}