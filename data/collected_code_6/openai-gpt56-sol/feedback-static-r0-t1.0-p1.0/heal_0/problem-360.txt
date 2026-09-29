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

    if (power > UINT64_MAX - 1) {
        return 0;
    }

    ++power;

    if (power != 0 && power > UINT64_MAX / power) {
        return 0;
    }

    *result = power * power - 2;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoul(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        input == 0 || input > UINT32_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!carol_number((uint32_t)input, &result)) {
        fprintf(stderr, "Carol number cannot be represented as uint64_t\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}