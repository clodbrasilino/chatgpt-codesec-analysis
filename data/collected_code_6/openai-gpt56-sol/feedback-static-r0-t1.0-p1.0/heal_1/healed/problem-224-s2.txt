#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int count_set_bits(uint64_t value)
{
    unsigned int count = 0U;

    while (value != UINT64_C(0)) {
        value &= value - UINT64_C(1);
        ++count;
    }

    return count;
}

int main(void)
{
    char buffer[128];
    char *end = NULL;
    uintmax_t parsed;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || parsed > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%u\n", count_set_bits((uint64_t)parsed)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}