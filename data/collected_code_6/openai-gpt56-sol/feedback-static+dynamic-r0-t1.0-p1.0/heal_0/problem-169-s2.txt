#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int pell_number(uint32_t n, uint64_t *result)
{
    if (result == NULL) {
        return -1;
    }

    if (n == 0U) {
        *result = 0U;
        return 0;
    }

    uint64_t previous = 0U;
    uint64_t current = 1U;

    for (uint32_t i = 2U; i <= n; ++i) {
        if (current > (UINT64_MAX - previous) / 2U) {
            return -1;
        }

        const uint64_t next = (2U * current) + previous;
        previous = current;
        current = next;
    }

    *result = current;
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    const uintmax_t parsed = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' || argv[1][0] == '-' ||
        parsed > UINT32_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    uint64_t result = 0U;

    if (pell_number((uint32_t)parsed, &result) != 0) {
        fprintf(stderr, "Result exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}