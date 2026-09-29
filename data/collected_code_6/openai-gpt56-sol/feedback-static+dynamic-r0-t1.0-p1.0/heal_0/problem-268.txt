#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int star_number(uint64_t n, uint64_t *result)
{
    if (n == 0 || result == NULL) {
        return 0;
    }

    if (n - 1 > (UINT64_MAX - 1) / 6) {
        return 0;
    }

    uint64_t a = n - 1;
    uint64_t b = n;

    if (a != 0 && b > (UINT64_MAX - 1) / 6 / a) {
        return 0;
    }

    *result = 6 * a * b + 1;
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    char *input = argv[1];
    uintmax_t parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || *end != '\0' ||
        parsed == 0 || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid positive integer\n");
        return EXIT_FAILURE;
    }

    uint64_t result;
    if (!star_number((uint64_t)parsed, &result)) {
        fprintf(stderr, "Result is outside the uint64_t range\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}