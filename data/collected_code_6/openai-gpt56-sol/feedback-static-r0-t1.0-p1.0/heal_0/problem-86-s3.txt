#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int centered_hexagonal_number(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t factor;

    if (result == NULL || n == 0) {
        return 0;
    }

    a = n - 1;

    if (n % 2 == 0) {
        a /= 2;
        factor = 6 * n - 3;
    } else {
        factor = 3 * n - 3;
    }

    if (a != 0 && factor > (UINT64_MAX - 1) / a) {
        return 0;
    }

    *result = a * factor + 1;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end;
    uintmax_t parsed;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || parsed == 0 || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid positive integer\n");
        return EXIT_FAILURE;
    }

    if (!centered_hexagonal_number((uint64_t)parsed, &result)) {
        fprintf(stderr, "Result is outside the uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}