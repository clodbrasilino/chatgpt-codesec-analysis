#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int catalan_number(uint32_t n, uint64_t *result)
{
    uint64_t value = 1;

    if (result == NULL) {
        return -1;
    }

    for (uint32_t k = 0; k < n; ++k) {
        const uint64_t factor = 2ULL * (2ULL * k + 1ULL);
        const uint64_t divisor = (uint64_t)k + 2ULL;

        if (value > UINT64_MAX / factor) {
            return -1;
        }

        value = (value * factor) / divisor;
    }

    *result = value;
    return 0;
}

int main(int argc, char *const argv[])
{
    char *end = NULL;
    unsigned long input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoul(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        argv[1][0] == '-' ||
        input > UINT32_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (catalan_number((uint32_t)input, &result) != 0) {
        fprintf(stderr, "Catalan number exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}