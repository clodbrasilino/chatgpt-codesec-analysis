#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int jacobsthal_lucas(uint32_t n, uint64_t *result)
{
    uint64_t previous = 2;
    uint64_t current = 1;

    if (result == NULL) {
        return 0;
    }

    if (n == 0U) {
        *result = previous;
        return 1;
    }

    for (uint32_t i = 1U; i < n; ++i) {
        if (previous > (UINT64_MAX - current) / 2U) {
            return 0;
        }

        const uint64_t next = current + (2U * previous);
        previous = current;
        current = next;
    }

    *result = current;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    input = strtoumax(argv[1], &end, 10);

    if (argv[1][0] == '\0' || end == argv[1] || *end != '\0' ||
        input > UINT32_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!jacobsthal_lucas((uint32_t)input, &result)) {
        fprintf(stderr, "Result exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}