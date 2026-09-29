#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static int count_tilings(size_t n, uint64_t *result)
{
    uint64_t previous = 1;
    uint64_t current = 3;

    if (result == NULL) {
        return -1;
    }

    if ((n & 1U) != 0U) {
        *result = 0;
        return 0;
    }

    if (n == 0U) {
        *result = previous;
        return 0;
    }

    for (size_t width = 4U; width <= n; width += 2U) {
        if (current > (UINT64_MAX + previous) / 4U) {
            return -1;
        }

        uint64_t next = 4U * current - previous;
        previous = current;
        current = next;
    }

    *result = current;
    return 0;
}

int main(void)
{
    char input[128];
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (errno != 0 || end == input || parsed > SIZE_MAX) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (count_tilings((size_t)parsed, &result) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}