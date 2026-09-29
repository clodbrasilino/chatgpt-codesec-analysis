#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>

static int cube_sum_even(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;

    if (result == NULL) {
        return -1;
    }

    a = n;
    b = n + 1U;

    if (b == 0U) {
        return -1;
    }

    if ((a & 1U) == 0U) {
        a /= 2U;
    } else {
        b /= 2U;
    }

    if (a != 0U && b > UINT64_MAX / a) {
        return -1;
    }

    a *= b;

    if (a != 0U && a > UINT64_MAX / a) {
        return -1;
    }

    a *= a;

    if (a > UINT64_MAX / 2U) {
        return -1;
    }

    *result = 2U * a;
    return 0;
}

int main(void)
{
    char input[128];
    char *end;
    uintmax_t parsed;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed > UINT64_MAX) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cube_sum_even((uint64_t)parsed, &result) != 0) {
        fputs("Result exceeds the supported range.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}