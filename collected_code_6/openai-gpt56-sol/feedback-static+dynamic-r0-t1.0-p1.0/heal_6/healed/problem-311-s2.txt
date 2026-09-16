#include <limits.h>
#include <stdio.h>

static unsigned int set_leftmost_unset_bit(unsigned int value)
{
    unsigned int mask = 1U << (sizeof(value) * CHAR_BIT - 1U);

    while (mask != 0U && (value & mask) != 0U) {
        mask >>= 1U;
    }

    return value | mask;
}

int main(void)
{
    unsigned int value;

    if (scanf("%u", &value) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("%u\n", set_leftmost_unset_bit(value));
    return 0;
}