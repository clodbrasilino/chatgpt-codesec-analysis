#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static int sum_of_squares(uint64_t n, uint64_t *result)
{
    uint64_t a = n;
    uint64_t b = n + 1U;
    uint64_t c = 2U * n + 1U;

    if (result == NULL || n > 3024616U) {
        return -1;
    }

    if ((a % 2U) == 0U) {
        a /= 2U;
    } else {
        b /= 2U;
    }

    if ((a % 3U) == 0U) {
        a /= 3U;
    } else if ((b % 3U) == 0U) {
        b /= 3U;
    } else {
        c /= 3U;
    }

    *result = a * b * c;
    return 0;
}

int main(void)
{
    char input[128];
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || parsed > UINT64_MAX) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_of_squares((uint64_t)parsed, &result) != 0) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}