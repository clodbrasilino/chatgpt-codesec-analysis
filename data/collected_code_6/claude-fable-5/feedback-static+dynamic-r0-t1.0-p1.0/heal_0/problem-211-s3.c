#include <stdio.h>
#include <stdlib.h>

unsigned long long countNumbers(unsigned int n)
{
    if (n == 0U) {
        return 0ULL;
    }
    if (n == 1U) {
        return 1ULL;
    }
    return 1ULL << (n - 2U);
}

int main(void)
{
    unsigned int n = 0U;
    int result;

    printf("Enter the number of bits: ");
    result = scanf("%u", &n);
    if (result != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n > 64U) {
        fprintf(stderr, "Bit count too large (max 64)\n");
        return EXIT_FAILURE;
    }

    printf("Count of %u-bit numbers with 0th and %uth bits set: %llu\n",
           n, (n > 0U) ? (n - 1U) : 0U, countNumbers(n));

    return EXIT_SUCCESS;
}