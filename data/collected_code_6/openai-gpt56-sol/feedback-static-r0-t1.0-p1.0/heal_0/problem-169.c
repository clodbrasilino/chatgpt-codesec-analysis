#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int pell_number(uint32_t n, uint64_t *result)
{
    uint64_t previous = 0U;
    uint64_t current = 1U;

    if (result == NULL) {
        return 0;
    }

    if (n == 0U) {
        *result = previous;
        return 1;
    }

    for (uint32_t i = 1U; i < n; ++i) {
        if (current > (UINT64_MAX - previous) / 2U) {
            return 0;
        }

        const uint64_t next = (2U * current) + previous;
        previous = current;
        current = next;
    }

    *result = current;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoul(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' || input > UINT32_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!pell_number((uint32_t)input, &result)) {
        fprintf(stderr, "Pell number exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}