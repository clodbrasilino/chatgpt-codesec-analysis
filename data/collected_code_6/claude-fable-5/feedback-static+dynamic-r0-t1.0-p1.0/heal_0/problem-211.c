#include <stdio.h>
#include <stdlib.h>

unsigned long long count_numbers(unsigned int n)
{
    if (n == 1U) {
        return 1ULL;
    }
    return 1ULL << (n - 2U);
}

int main(void)
{
    unsigned int n;

    printf("Enter the number of bits (n): ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n == 0U || n > 63U) {
        fprintf(stderr, "Error: n must be between 1 and 63.\n");
        return EXIT_FAILURE;
    }

    printf("Count of numbers with 0th and %uth bits set: %llu\n",
           n - 1U, count_numbers(n));

    return EXIT_SUCCESS;
}