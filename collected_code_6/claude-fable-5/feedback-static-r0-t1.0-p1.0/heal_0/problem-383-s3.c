#include <stdio.h>
#include <stdlib.h>

unsigned int toggle_odd_bits(unsigned int num)
{
    unsigned int mask = 0xAAAAAAAAu;
    return num ^ mask;
}

int main(void)
{
    unsigned int number;
    unsigned int result;

    printf("Enter an unsigned integer: ");
    if (scanf("%u", &number) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = toggle_odd_bits(number);

    printf("Original number: %u (0x%08X)\n", number, number);
    printf("After toggling odd bits: %u (0x%08X)\n", result, result);

    return EXIT_SUCCESS;
}