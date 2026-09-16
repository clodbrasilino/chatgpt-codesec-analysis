#include <limits.h>
#include <stdio.h>

static unsigned int toggle_inner_bits(unsigned int value)
{
    const unsigned int bit_count = (unsigned int)(sizeof(value) * CHAR_BIT);
    const unsigned int first_bit = 1U;
    const unsigned int last_bit = 1U << (bit_count - 1U);
    const unsigned int inner_mask = ~(first_bit | last_bit);

    return value ^ inner_mask;
}

int main(void)
{
    unsigned int value = 0U;

    if (scanf("%u", &value) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("%u\n", toggle_inner_bits(value));
    return 0;
}