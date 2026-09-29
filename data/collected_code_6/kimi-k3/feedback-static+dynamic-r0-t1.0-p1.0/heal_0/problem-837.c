#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t cube_sum_odd_natural(unsigned int n)
{
    uint64_t sum = 0;
    uint64_t odd_number = 1;
    unsigned int i;

    for (i = 0; i < n; ++i) {
        sum += odd_number * odd_number * odd_number;
        odd_number += 2;
    }

    return sum;
}

int main(void)
{
    unsigned int n;
    int scan_result;

    printf("Enter the value of n: ");
    scan_result = scanf("%u", &n);

    if (scan_result != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("Cube sum of first %u odd natural numbers: %" PRIu64 "\n", n, cube_sum_odd_natural(n));

    return 0;
}