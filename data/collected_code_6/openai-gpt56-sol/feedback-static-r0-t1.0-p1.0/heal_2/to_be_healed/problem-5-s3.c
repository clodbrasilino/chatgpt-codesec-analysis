#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
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

    for (unsigned int i = 4U; i <= n;) {
        if (current > UINT64_MAX / 4U ||
            previous > 4U * current ||
            4U * current - previous > UINT64_MAX) {
            return -1;
        }

        uint64_t next = 4U * current - previous;
        previous = current;
        current = next;

        if (n - i < 2U) {
            break;
        }
        i += 2U;
    }

    *result = current;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    char *end;
    unsigned long value;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoul(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT_MAX) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' ||
           *end == '\n' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
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