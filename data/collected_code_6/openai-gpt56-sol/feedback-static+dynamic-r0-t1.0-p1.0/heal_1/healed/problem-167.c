#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static int next_power_of_two(uint64_t n, uint64_t *result)
{
    if (result == NULL || n == 0 || n > (UINT64_C(1) << 63)) {
        return -1;
    }

    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n |= n >> 32;

    *result = n + 1;
    return 0;
}

int main(int argc, char *const argv[])
{
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive-integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        parsed == 0 || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid positive integer\n");
        return EXIT_FAILURE;
    }

    if (next_power_of_two((uint64_t)parsed, &result) != 0) {
        fprintf(stderr,
                "No representable power of two is greater than or equal to the input\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}