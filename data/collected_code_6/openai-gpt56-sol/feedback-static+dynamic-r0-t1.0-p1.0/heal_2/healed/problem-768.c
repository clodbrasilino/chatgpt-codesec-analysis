#include <stdbool.h>
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
    uint64_t value;
    char extra;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    if (sscanf(input, " %" SCNu64 " %c", &value, &extra) != 1) {
        return 1;
    }

    if (printf("%s\n", has_odd_parity(value) ? "Odd parity" : "Even parity") < 0) {
        return 1;
    }

    return 0;
}