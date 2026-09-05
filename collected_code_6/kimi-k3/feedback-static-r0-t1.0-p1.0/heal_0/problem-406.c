#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int find_parity(uint64_t num)
{
    return (int)(num & 1U);
}

int main(void)
{
    uint64_t num;
    int scan_result;
    int parity;

    printf("Enter a non-negative integer: ");
    scan_result = scanf("%" SCNu64, &num);

    if (scan_result != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    parity = find_parity(num);

    if (parity == 0)
    {
        printf("The number is even\n");
    }
    else
    {
        printf("The number is odd\n");
    }

    return 0;
}