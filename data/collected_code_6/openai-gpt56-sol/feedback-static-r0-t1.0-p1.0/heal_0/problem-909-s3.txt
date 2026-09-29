#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_palindrome(uint64_t number)
{
    uint64_t original = number;
    uint64_t reversed = 0;

    do {
        reversed = reversed * 10U + number % 10U;
        number /= 10U;
    } while (number != 0U);

    return original == reversed;
}

static int previous_palindrome(uint64_t number, uint64_t *result)
{
    if (result == NULL || number == 0U) {
        return 0;
    }

    for (uint64_t candidate = number - 1U;; --candidate) {
        if (is_palindrome(candidate)) {
            *result = candidate;
            return 1;
        }

        if (candidate == 0U) {
            break;
        }
    }

    return 0;
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

    if (errno == ERANGE || end == argv[1] || *end != '\0' || argv[1][0] == '-' ||
        parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid number\n");
        return EXIT_FAILURE;
    }

    if (!previous_palindrome((uint64_t)parsed, &result)) {
        fprintf(stderr, "No previous non-negative palindrome exists\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}