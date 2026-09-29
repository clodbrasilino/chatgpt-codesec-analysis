#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_sequences(unsigned int n, uint64_t *result)
{
    uint64_t value = 1;

    if (result == NULL) {
        return -1;
    }

    for (unsigned int k = 1; k <= n; ++k) {
        const uint64_t numerator = (uint64_t)n + k;

        if (value > UINT64_MAX / numerator) {
            return -1;
        }

        value *= numerator;
        value /= k;
    }

    *result = value;
    return 0;
}

int main(int argc, const char *const argv[])
{
    char *end = NULL;
    unsigned long input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoul(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        input > UINT32_MAX) {
        fprintf(stderr, "Invalid value for n\n");
        return EXIT_FAILURE;
    }

    if (count_sequences((unsigned int)input, &result) != 0) {
        fprintf(stderr, "Result exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}