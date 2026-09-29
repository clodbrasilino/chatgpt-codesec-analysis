#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

static bool has_even_parity(uint64_t value)
{
    bool parity = false;

    while (value != UINT64_C(0)) {
        parity = !parity;
        value &= value - UINT64_C(1);
    }

    return !parity;
}

int main(void)
{
    uint64_t value;

    if (scanf("%" SCNu64, &value) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    puts(has_even_parity(value) ? "Even parity" : "Odd parity");
    return 0;
}