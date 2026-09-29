#include <stdbool.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

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
    char input[64];
    char *end;
    uintmax_t parsed;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    char *newline = NULL;

    for (size_t i = 0; input[i] != '\0'; ++i) {
        if (input[i] == '\n') {
            newline = &input[i];
            break;
        }
    }

    if (newline == NULL && !feof(stdin)) {
        return 1;
    }

    errno = 0;
    end = input;
    parsed = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed > UINT64_MAX) {
        return 1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return 1;
    }

    if (printf("%s\n",
               has_odd_parity((uint64_t)parsed)
                   ? "Odd parity"
                   : "Even parity") < 0) {
        return 1;
    }

    return 0;
}