#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int nth_polite_number(uint64_t n, uint64_t *result)
{
    uint64_t polite_count = 0;

    if (n == 0 || result == NULL) {
        return 0;
    }

    for (uint64_t value = 3; value < UINT64_MAX; ++value) {
        uint64_t odd_part = value;

        while ((odd_part & UINT64_C(1)) == 0) {
            odd_part >>= 1;
        }

        if (odd_part > 1 && ++polite_count == n) {
            *result = value;
            return 1;
        }
    }

    return 0;
}

int main(int argc, const char *const argv[])
{
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed == 0 || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!nth_polite_number((uint64_t)parsed, &result)) {
        fprintf(stderr, "Unable to compute the requested polite number\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}