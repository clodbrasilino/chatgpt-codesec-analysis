#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_odd_parity(unsigned long long value)
{
    bool odd = false;

    while (value != 0ULL) {
        odd = !odd;
        value &= value - 1ULL;
    }

    return odd;
}

int main(void)
{
    unsigned long long value;

    if (scanf("%llu", &value) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%s\n", has_odd_parity(value) ? "Odd parity" : "Even parity");
    return EXIT_SUCCESS;
}