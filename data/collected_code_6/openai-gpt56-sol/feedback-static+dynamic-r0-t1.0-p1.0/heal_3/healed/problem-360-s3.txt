#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int carol_number(uint32_t n, uint64_t *result)
{
    uint64_t power = 1;

    if (n == 0 || result == NULL) {
        return 0;
    }

    for (uint32_t i = 0; i < n; ++i) {
        if (power > UINT64_MAX / 2) {
            return 0;
        }
        power *= 2;
    }

    const uint64_t base = power - 1;

    if (base > UINT64_MAX / base) {
        return 0;
    }

    const uint64_t square = base * base;

    if (square < 2) {
        return 0;
    }

    *result = square - 2;
    return 1;
}

int main(int argc, const char *const argv[])
{
    char *end = NULL;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive-index>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    const unsigned long parsed = strtoul(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        parsed == 0 || parsed > UINT32_MAX) {
        fprintf(stderr, "Invalid index\n");
        return EXIT_FAILURE;
    }

    if (!carol_number((uint32_t)parsed, &result)) {
        fprintf(stderr, "Carol number exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}