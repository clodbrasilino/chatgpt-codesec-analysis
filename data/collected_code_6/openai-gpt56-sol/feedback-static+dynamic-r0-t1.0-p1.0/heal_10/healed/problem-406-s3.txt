#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int parity(unsigned long long value)
{
    unsigned int result = 0U;

    while (value != 0ULL) {
        result ^= 1U;
        value &= value - 1ULL;
    }

    return result;
}

int main(void)
{
    char buffer[256];
    char *end;
    unsigned long long value;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (buffer[0] == '\0') {
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoull(buffer, &end, 0);

    if (errno == ERANGE || end == buffer) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (printf("%u\n", parity(value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}