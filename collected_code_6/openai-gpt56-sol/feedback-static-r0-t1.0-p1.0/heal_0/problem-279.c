#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int decagonal_number(uint64_t n, uint64_t *result)
{
    if (result == NULL || n == 0) {
        return 0;
    }

    if (n > UINT64_MAX / 8U) {
        return 0;
    }

    uint64_t factor = 8U * n - 6U;

    if (n > UINT64_MAX / factor) {
        return 0;
    }

    *result = n * factor / 2U;
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
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    uint64_t result = 0;

    if (!decagonal_number((uint64_t)input, &result)) {
        fprintf(stderr, "Result is out of range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}