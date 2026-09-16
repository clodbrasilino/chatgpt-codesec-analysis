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
        reversed = reversed * 10U + value % 10U;
        value /= 10U;
    } while (value != 0U);

    return original == reversed;
}

static int next_smallest_palindrome(uint64_t number, uint64_t *result)
{
    uint64_t candidate;

    if (result == NULL || number == UINT64_MAX) {
        return 0;
    }

    candidate = number + 1U;

    for (;;) {
        if (is_palindrome(candidate)) {
            *result = candidate;
            return 1;
        }

        if (candidate == UINT64_MAX) {
            return 0;
        }

        ++candidate;
    }
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || parsed > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!next_smallest_palindrome((uint64_t)parsed, &result)) {
        fputs("No larger palindrome is representable\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}