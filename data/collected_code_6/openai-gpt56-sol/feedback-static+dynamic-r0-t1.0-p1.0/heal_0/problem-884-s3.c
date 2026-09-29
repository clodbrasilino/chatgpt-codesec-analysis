#include <stdbool.h>
#include <stdio.h>

static bool are_all_set_bits_in_range(unsigned int value,
                                      unsigned int lower,
                                      unsigned int upper)
{
    const unsigned int bit_count = (unsigned int)(sizeof(value) * 8U);

    if (lower > upper || upper >= bit_count) {
        return false;
    }

    value >>= lower;
    value >>= upper - lower + 1U;

    return value == 0U;
}

int main(void)
{
    unsigned int value;
    unsigned int lower;
    unsigned int upper;

    if (scanf("%u %u %u", &value, &lower, &upper) != 3) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    printf("%s\n",
           are_all_set_bits_in_range(value, lower, upper) ? "true" : "false");

    return 0;
}