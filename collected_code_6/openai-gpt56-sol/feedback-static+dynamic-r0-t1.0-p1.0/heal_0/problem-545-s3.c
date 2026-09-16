#include <stdio.h>
#include <limits.h>

static unsigned int toggle_first_and_last_bits(unsigned int value)
{
    const unsigned int mask = 1U | (1U << (sizeof(value) * CHAR_BIT - 1U));
    return value ^ mask;
}

int main(void)
{
    unsigned int value;

    if (scanf("%u", &value) != 1) {
        return 1;
    }

    printf("%u\n", toggle_first_and_last_bits(value));
    return 0;
}