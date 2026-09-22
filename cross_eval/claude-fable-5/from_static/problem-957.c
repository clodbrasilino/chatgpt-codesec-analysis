#include <stdio.h>
#include <stdlib.h>

int get_rightmost_set_bit_position(unsigned int n)
{
    int position;
    unsigned int mask;

    if (n == 0U)
    {
        return -1;
    }

    position = 1;
    mask = 1U;

    while ((n & mask) == 0U)
    {
        mask <<= 1;
        position++;
    }

    return position;
}

int main(void)
{
    unsigned int number;
    int result;

    printf("Enter a non-negative integer: ");

    if (scanf("%u", &number) != 1)
    {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    result = get_rightmost_set_bit_position(number);

    if (result == -1)
    {
        printf("No set bit found in %u.\n", number);
    }
    else
    {
        printf("Position of rightmost set bit in %u is %d.\n", number, result);
    }

    return EXIT_SUCCESS;
}