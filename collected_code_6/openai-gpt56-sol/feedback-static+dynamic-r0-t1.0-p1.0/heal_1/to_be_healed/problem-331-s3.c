#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got 31
  *  test case 1 failed: expected 2, got 31
  *  test case 2 failed: expected 1, got 30
  */

static unsigned int count_unset_bits(unsigned int value)
{
    unsigned int count = 0U;

    for (unsigned int i = 0U; i < (unsigned int)(sizeof(value) * CHAR_BIT); ++i) {
        if ((value & 1U) == 0U) {
            ++count;
        }
        value >>= 1U;
    }

    return count;
}

int main(void)
{
    unsigned int value;

    if (scanf("%u", &value) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%u\n", count_unset_bits(value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}