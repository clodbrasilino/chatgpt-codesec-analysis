#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t set_odd_bits(uint32_t num)
{
    uint32_t mask = 0xAAAAAAAAU;
    return num | mask;
}

int main(void)
{
    uint32_t number = 0U;
    uint32_t result = 0U;

    printf("Enter an unsigned integer: ");
    if (scanf("%u", &number) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = set_odd_bits(number);

    printf("Original number: %u (0x%08X)\n", number, number);
    printf("After setting odd bits: %u (0x%08X)\n", result, result);

    return EXIT_SUCCESS;
}