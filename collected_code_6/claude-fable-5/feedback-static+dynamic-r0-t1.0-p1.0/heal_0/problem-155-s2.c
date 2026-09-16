#include <stdio.h>
#include <stdlib.h>

unsigned int toggle_even_bits(unsigned int num)
{
    unsigned int mask = 0x55555555U;
    return num ^ mask;
}

int main(void)
{
    unsigned int number = 0U;
    unsigned int result = 0U;

    printf("Enter an unsigned integer: ");
    if (scanf("%u", &number) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = toggle_even_bits(number);

    printf("Original number: %u\n", number);
    printf("After toggling even bits: %u\n", result);

    return EXIT_SUCCESS;
}