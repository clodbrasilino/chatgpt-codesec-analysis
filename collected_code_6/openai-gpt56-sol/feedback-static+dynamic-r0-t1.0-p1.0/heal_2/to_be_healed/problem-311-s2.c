#include <limits.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got 31
  *  test case 0 failed: expected 14, got 26
  *  test case 1 failed: expected 14, got 28
  */

static unsigned int set_leftmost_unset_bit(unsigned int value)
{
    unsigned int mask = 1U;

    while (mask <= value && mask <= UINT_MAX / 2U) {
        mask <<= 1U;
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