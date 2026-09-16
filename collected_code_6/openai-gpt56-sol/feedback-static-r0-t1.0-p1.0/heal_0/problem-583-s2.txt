#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int catalan(unsigned int n, uint64_t *result)
{
    uint64_t value = 1;

    if (result == NULL) {
        return -1;
    }

    for (unsigned int k = 0; k < n; ++k) {
        uint64_t multiplier = 2U * (2U * (uint64_t)k + 1U);
        uint64_t divisor = (uint64_t)k + 2U;

        if (value > UINT64_MAX / multiplier) {
            return -1;
        }

        value = (value * multiplier) / divisor;
    }

    *result = value;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long parsed;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoul(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' || parsed > UINT32_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (catalan((unsigned int)parsed, &result) != 0) {
        fprintf(stderr, "Catalan number exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}