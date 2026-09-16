#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int hexagonal_number(uint64_t n, uint64_t *result)
{
    if (result == NULL || n == 0 || n > (UINT64_MAX / 2U) + 1U) {
        return 0;
    }

    uint64_t factor = (2U * n) - 1U;

    if (n > UINT64_MAX / factor) {
        return 0;
    }

    *result = n * factor;
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *end = NULL;
    uintmax_t input = strtoumax(argv[1], &end, 10);

    if (argv[1][0] == '\0' || end == argv[1] || *end != '\0' ||
        input == 0 || input > UINT64_MAX) {
        fprintf(stderr, "Invalid positive integer.\n");
        return EXIT_FAILURE;
    }

    uint64_t result = 0;

    if (!hexagonal_number((uint64_t)input, &result)) {
        fprintf(stderr, "The result exceeds the supported range.\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}