#include <stdio.h>
#include <limits.h>

unsigned int left_rotate(unsigned int value, unsigned int shift)
{
    const unsigned int bits = (unsigned int)(sizeof(unsigned int) * CHAR_BIT);

    shift %= bits;

    if (shift == 0U)
    {
        return value;
    }

    return (value << shift) | (value >> (bits - shift));
}

int main(void)
{
    unsigned int number = 0U;
    unsigned int shift = 0U;

    printf("Enter an unsigned integer: ");
    if (scanf("%u", &number) != 1)
    {
        fprintf(stderr, "Invalid input for number.\n");
        return 1;
    }

    printf("Enter number of positions to rotate left: ");
    if (scanf("%u", &shift) != 1)
    {
        fprintf(stderr, "Invalid input for shift.\n");
        return 1;
    }

    printf("Result: %u\n", left_rotate(number, shift));

    return 0;
}