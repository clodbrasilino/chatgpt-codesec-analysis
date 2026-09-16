#include <limits.h>
#include <stdint.h>
#include <stdio.h>

static int most_significant_set_bit(uintmax_t value)
{
    int bit_number = -1;

    while (value != 0U) {
        ++bit_number;
        value >>= 1U;
    }

    return bit_number;
}

int main(void)
{
    uintmax_t value;

    if (scanf("%ju", &value) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    printf("%d\n", most_significant_set_bit(value));
    return 0;
}