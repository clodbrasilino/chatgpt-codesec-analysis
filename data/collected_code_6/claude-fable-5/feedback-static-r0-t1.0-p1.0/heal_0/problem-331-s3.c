#include <stdio.h>
#include <stdlib.h>

unsigned int count_unset_bits(unsigned int n)
{
    unsigned int count = 0;

    if (n == 0U) {
        return 1U;
    }

    while (n > 0U) {
        if ((n & 1U) == 0U) {
            count++;
        }
        n >>= 1U;
    }

    return count;
}

int main(void)
{
    unsigned int number = 0U;

    printf("Enter a non-negative integer: ");

    if (scanf("%u", &number) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    printf("Number of unset bits in %u: %u\n", number, count_unset_bits(number));

    return EXIT_SUCCESS;
}