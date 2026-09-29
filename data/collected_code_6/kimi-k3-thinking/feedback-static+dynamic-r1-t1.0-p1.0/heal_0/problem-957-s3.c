#include <stdio.h>

int getRightmostSetBitPosition(unsigned int n);

int getRightmostSetBitPosition(unsigned int n)
{
    int position = 1;

    if (n == 0U)
    {
        return 0;
    }

    while ((n & 1U) == 0U)
    {
        n >>= 1U;
        position++;
    }

    return position;
}

int main(void)
{
    unsigned int number = 0U;
    int position;

    printf("Enter an unsigned integer: ");
    if (scanf("%u", &number) != 1)
    {
        printf("Invalid input.\n");
        return 1;
    }

    position = getRightmostSetBitPosition(number);

    if (position == 0)
    {
        printf("The number %u has no set bits.\n", number);
    }
    else
    {
        printf("The position of the rightmost set bit in %u is %d.\n", number, position);
    }

    return 0;
}