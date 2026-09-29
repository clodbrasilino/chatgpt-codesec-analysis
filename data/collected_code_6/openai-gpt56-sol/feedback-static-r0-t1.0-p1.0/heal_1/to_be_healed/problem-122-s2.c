#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int nth_smart_number(uint64_t n, uint64_t *result)
{
    if (n == 0 || result == NULL) {
        return 0;
    }

    uint64_t value = 1;

    for (uint64_t i = 1; i < n; ++i) {
        if (value > UINT64_MAX / 2) {
            return 0;
        }
        value *= 2;
    }

    *result = value;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end = NULL;
    uint64_t n;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoumax(input, &end, 10);

    if (errno != 0 || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r') {
        ++end;
    }

    if (*end != '\0' || !nth_smart_number(n, &result)) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}