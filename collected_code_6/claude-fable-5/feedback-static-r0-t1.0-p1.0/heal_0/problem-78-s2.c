#include <stdio.h>
#include <stdlib.h>

static int has_odd_set_bits(unsigned long n)
{
    int parity = 0;

    while (n != 0UL) {
        parity ^= 1;
        n &= (n - 1UL);
    }

    return parity;
}

static unsigned long count_odd_set_bits(unsigned long n)
{
    unsigned long count = 0UL;
    unsigned long i;

    for (i = 1UL; i <= n; i++) {
        if (has_odd_set_bits(i) == 1) {
            count++;
        }
        if (i == n) {
            break;
        }
    }

    return count;
}

int main(void)
{
    unsigned long n = 0UL;
    unsigned long result;
    int ret;

    printf("Enter a non-negative integer: ");

    ret = scanf("%lu", &n);
    if (ret != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    result = count_odd_set_bits(n);

    printf("Number of integers from 1 to %lu with an odd number of set bits: %lu\n", n, result);

    return EXIT_SUCCESS;
}