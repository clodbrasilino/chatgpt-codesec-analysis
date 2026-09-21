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
    uintmax_t parsed;
    int ch;

    errno = 0;

    if (scanf("%" SCNuMAX, &parsed) != 1 ||
        errno == ERANGE ||
        parsed > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    do {
        ch = getchar();
    } while (ch == ' ' || ch == '\t' || ch == '\r' ||
             ch == '\f' || ch == '\v');

    if (ch != '\n' && ch != EOF) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n",
               has_odd_parity((uint64_t)parsed)
                   ? "Odd parity"
                   : "Even parity") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}