#include <stdbool.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_odd_parity(uint64_t value)
{
    bool odd = false;

    while (value != UINT64_C(0)) {
        odd = !odd;
        value &= value - UINT64_C(1);
    }

    return odd;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    char *end;
    uintmax_t parsed;

    if (getline(&input, &capacity, stdin) < 0) {
        free(input);
        return 1;
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (input == end || errno == ERANGE || parsed > UINT64_MAX) {
        free(input);
        return 1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return 1;
    }

    free(input);

    if (printf("%s\n",
               has_odd_parity((uint64_t)parsed)
                   ? "Odd parity"
                   : "Even parity") < 0) {
        return 1;
    }

    return 0;
}