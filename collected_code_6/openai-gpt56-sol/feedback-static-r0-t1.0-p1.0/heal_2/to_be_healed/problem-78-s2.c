#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_uintmax(uintmax_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    char *end = NULL;
    errno = 0;
    uintmax_t result = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = result;
    return 1;
}

static unsigned int has_odd_parity(uint64_t value)
{
    unsigned int parity = 0U;

    while (value != UINT64_C(0)) {
        parity ^= 1U;
        value &= value - UINT64_C(1);
    }

    return parity;
}

int main(void)
{
    uintmax_t input_count;

    if (!read_uintmax(&input_count) || input_count > SIZE_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    size_t count = (size_t)input_count;
    size_t odd_count = 0U;

    for (size_t i = 0U; i < count; ++i) {
        uintmax_t input_value;

        if (!read_uintmax(&input_value) || input_value > UINT64_MAX) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        odd_count += has_odd_parity((uint64_t)input_value);
    }

    if (printf("%zu\n", odd_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}