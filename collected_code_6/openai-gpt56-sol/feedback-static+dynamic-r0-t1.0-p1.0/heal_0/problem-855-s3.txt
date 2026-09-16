#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>

static int has_even_parity(uintmax_t value)
{
    int parity = 0;

    while (value != 0U) {
        parity ^= 1;
        value &= value - 1U;
    }

    return parity == 0;
}

int main(void)
{
    char input[128];
    char *end = NULL;
    uintmax_t value;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 0);

    if (errno != 0 || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", has_even_parity(value) ? "Even parity" : "Odd parity") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}