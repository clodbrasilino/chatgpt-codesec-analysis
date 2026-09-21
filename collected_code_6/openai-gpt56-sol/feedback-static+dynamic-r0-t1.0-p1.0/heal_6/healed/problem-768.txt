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
    uintmax_t parsed;
    int trailing;

    if (scanf("%" SCNuMAX, &parsed) != 1) {
        return 1;
    }

    if (parsed > UINT64_MAX) {
        return 1;
    }

    do {
        trailing = getchar();
    } while (trailing == ' ' || trailing == '\t' || trailing == '\r' ||
             trailing == '\f' || trailing == '\v');

    if (trailing != '\n' && trailing != EOF) {
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