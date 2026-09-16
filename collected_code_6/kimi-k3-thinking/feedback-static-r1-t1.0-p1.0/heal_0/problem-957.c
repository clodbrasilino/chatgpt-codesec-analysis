#include <stdio.h>

int rightmost_set_bit_position(unsigned int n)
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
    unsigned int n = 0U;
    int position;

    printf("Enter a number: ");

    if (scanf("%u", &n) != 1)
    {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    position = rightmost_set_bit_position(n);

    if (position == 0)
    {
        printf("The number 0 has no set bits.\n");
    }
    else
    {
        printf("Position of rightmost set bit: %d\n", position);
    }

    return 0;
}