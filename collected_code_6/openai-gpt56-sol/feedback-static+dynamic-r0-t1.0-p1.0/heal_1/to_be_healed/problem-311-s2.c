#include <limits.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 14, got 2147483658
  *  test case 2 failed: expected 15, got 2147483663
  *  test case 1 failed: expected 14, got 2147483660
  */

static unsigned int set_leftmost_unset_bit(unsigned int value)
{
    const unsigned int bit_count = (unsigned int)(sizeof(value) * CHAR_BIT);

    for (unsigned int index = bit_count; index > 0U; --index) {
        const unsigned int mask = 1U << (index - 1U);

        if ((value & mask) == 0U) {
            return value | mask;
        }
    }

    return value;
}

int main(void)
{
    unsigned int value = 0U;

    if (scanf("%u", &value) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("%u\n", set_leftmost_unset_bit(value));
    return 0;
}