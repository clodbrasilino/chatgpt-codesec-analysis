#include <stdio.h>
#include <stdlib.h>

unsigned int toggle_odd_bits(unsigned int num)
{
    unsigned int mask = 0xAAAAAAAAU;
    return num ^ mask;
}

int main(void)
{
    unsigned int number = 0U;
    unsigned int result = 0U;
    int scan_status = 0;

    printf("Enter an unsigned integer: ");
    scan_status = scanf("%u", &number);

    if (scan_status != 1)
    {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    result = toggle_odd_bits(number);

    printf("Original number: %u\n", number);
    printf("After toggling odd bits: %u\n", result);

    return EXIT_SUCCESS;
}