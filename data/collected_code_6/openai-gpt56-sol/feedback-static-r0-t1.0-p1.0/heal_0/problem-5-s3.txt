#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static int count_tilings(unsigned int n, uint64_t *result)
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
        *result = 1;
        return 0;
    }

    for (unsigned int i = 4U; i <= n; i += 2U) {
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
    char input[64];
    char *end = NULL;
    unsigned long value;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoul(input, &end, 10);

    if (errno != 0 || end == input || value > UINT_MAX) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (count_tilings((unsigned int)value, &result) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}