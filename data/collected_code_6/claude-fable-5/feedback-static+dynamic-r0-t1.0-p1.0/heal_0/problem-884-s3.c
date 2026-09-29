#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

static bool all_bits_set_in_range(unsigned int n, unsigned int l, unsigned int r)
{
    unsigned int total_bits;
    unsigned int upper_mask;
    unsigned int lower_mask;
    unsigned int mask;

    total_bits = (unsigned int)(sizeof(unsigned int) * (size_t)CHAR_BIT);

    if ((l < 1U) || (l > r) || (r > total_bits))
    {
        return false;
    }

    if (r == total_bits)
    {
        upper_mask = UINT_MAX;
    }
    else
    {
        upper_mask = (1U << r) - 1U;
    }

    lower_mask = (1U << (l - 1U)) - 1U;
    mask = upper_mask & (~lower_mask);

    return ((n & mask) == mask);
}

int main(void)
{
    unsigned int number;
    unsigned int low;
    unsigned int high;
    int scanned;

    printf("Enter the number: ");
    scanned = scanf("%u", &number);
    if (scanned != 1)
    {
        fprintf(stderr, "Invalid input for number.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the lower bit position (1-based): ");
    scanned = scanf("%u", &low);
    if (scanned != 1)
    {
        fprintf(stderr, "Invalid input for lower bit position.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the higher bit position (1-based): ");
    scanned = scanf("%u", &high);
    if (scanned != 1)
    {
        fprintf(stderr, "Invalid input for higher bit position.\n");
        return EXIT_FAILURE;
    }

    if ((low < 1U) || (low > high) ||
        (high > (unsigned int)(sizeof(unsigned int) * (size_t)CHAR_BIT)))
    {
        fprintf(stderr, "Bit range is out of bounds.\n");
        return EXIT_FAILURE;
    }

    if (all_bits_set_in_range(number, low, high))
    {
        printf("All bits are set in the given range.\n");
    }
    else
    {
        printf("Not all bits are set in the given range.\n");
    }

    return EXIT_SUCCESS;
}