#include <stdio.h>
#include <stdlib.h>

static unsigned int toggle_middle_bits(unsigned int n)
{
    unsigned int mask;
    unsigned int temp;
    unsigned int msb_pos;

    if (n <= 2U)
    {
        return n;
    }

    temp = n;
    msb_pos = 0U;
    while (temp > 1U)
    {
        temp >>= 1U;
        msb_pos++;
    }

    mask = ((1U << msb_pos) - 1U) & ~1U;

    return n ^ mask;
}

int main(void)
{
    unsigned int number;
    unsigned int result;
    int scan_status;

    printf("Enter an unsigned integer: ");
    scan_status = scanf("%u", &number);
    if (scan_status != 1)
    {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    result = toggle_middle_bits(number);
    printf("Original number: %u\n", number);
    printf("After toggling middle bits: %u\n", result);

    return EXIT_SUCCESS;
}