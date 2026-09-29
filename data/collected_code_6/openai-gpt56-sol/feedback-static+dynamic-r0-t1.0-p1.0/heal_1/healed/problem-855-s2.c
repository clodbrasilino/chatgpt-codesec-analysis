#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

static bool has_even_parity(uint64_t value)
{
    bool even = true;

    while (value != UINT64_C(0)) {
        even = !even;
        value &= value - UINT64_C(1);
    }

    return even;
}

int main(void)
{
    char input[128];
    uint64_t value;
    char trailing;

    if (fgets(input, sizeof input, stdin) == NULL ||
        sscanf(input, " %" SCNu64 " %c", &value, &trailing) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    puts(has_even_parity(value) ? "Even parity" : "Odd parity");
    return 0;
}