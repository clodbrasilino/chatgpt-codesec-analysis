#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int tetrahedral_number(uint64_t n, uint64_t *result)
{
    uint64_t a = n;
    uint64_t b;
    uint64_t c;

    if (result == NULL || n > UINT64_MAX - 2U) {
        return 0;
    }

    b = n + 1U;
    c = n + 2U;

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

    if (a != 0U && b > UINT64_MAX / a) {
        return 0;
    }

    a *= b;

    if (a != 0U && c > UINT64_MAX / a) {
        return 0;
    }

    *result = a * c;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid nonnegative integer.\n");
        return EXIT_FAILURE;
    }

    if (!tetrahedral_number((uint64_t)parsed, &result)) {
        fprintf(stderr, "Result exceeds uint64_t range.\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}