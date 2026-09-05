#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int check_even_parity(uint32_t num)
{
    uint32_t v = num;
    v ^= v >> 16;
    v ^= v >> 8;
    v ^= v >> 4;
    v ^= v >> 2;
    v ^= v >> 1;
    return (int)(v & 1U);
}

int main(void)
{
    uint32_t num = 0;
    int scan_result = 0;

    printf("Enter an unsigned integer: ");
    scan_result = scanf("%" SCNu32, &num);

    if (scan_result != 1) {
        fprintf(stderr, "Error: Invalid input.\n");
        return 1;
    }

    if (check_even_parity(num) == 0) {
        printf("The number has even parity.\n");
    } else {
        printf("The number does not have even parity.\n");
    }

    return 0;
}