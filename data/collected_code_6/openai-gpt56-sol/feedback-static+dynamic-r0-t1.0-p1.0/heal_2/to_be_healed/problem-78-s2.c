#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_size(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || parsed > SIZE_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || parsed > UINT64_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static unsigned int has_odd_set_bits(uint64_t value)
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
    size_t count = 0U;

    if (!read_size(&count)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    size_t odd_count = 0U;

    for (size_t i = 0U; i < count; ++i) {
        uint64_t value = UINT64_C(0);

        if (!read_uint64(&value)) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        odd_count += has_odd_set_bits(value);
    }

    if (printf("%zu\n", odd_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}