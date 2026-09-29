#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int nonagonal_number(uint64_t n, uint64_t *result)
{
    if (result == NULL || n == 0 || n > UINT64_MAX / 7) {
        return 0;
    }

    const uint64_t factor = 7 * n - 5;

    if (n > UINT64_MAX / factor) {
        return 0;
    }

    *result = n * factor / 2;
    return 1;
}

int main(int argc, char *const argv[const])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    const uintmax_t parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed == 0 || parsed > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    uint64_t result;

    if (!nonagonal_number((uint64_t)parsed, &result)) {
        fputs("Result is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}