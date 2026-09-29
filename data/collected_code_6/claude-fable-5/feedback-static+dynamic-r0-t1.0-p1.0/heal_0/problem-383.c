#include <stdio.h>
#include <stdlib.h>

unsigned int toggle_odd_bits(unsigned int num)
{
    unsigned int mask = 0xAAAAAAAAu;
    return num ^ mask;
}

int main(void)
{
    unsigned int number = 0;
    unsigned int result = 0;

    printf("Enter a non-negative number: ");
    if (scanf("%u", &number) != 1)
    {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    result = toggle_odd_bits(number);

    printf("Original number: %u (0x%X)\n", number, number);
    printf("After toggling odd bits: %u (0x%X)\n", result, result);

    return EXIT_SUCCESS;
}