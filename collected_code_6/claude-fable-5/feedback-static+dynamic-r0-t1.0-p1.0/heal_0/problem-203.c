#include <stdio.h>
#include <stdlib.h>

int hamming_distance(unsigned int a, unsigned int b)
{
    unsigned int x = a ^ b;
    int count = 0;

    while (x != 0U) {
        count += (int)(x & 1U);
        x >>= 1U;
    }

    return count;
}

int main(void)
{
    unsigned int a;
    unsigned int b;

    printf("Enter first integer: ");
    if (scanf("%u", &a) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter second integer: ");
    if (scanf("%u", &b) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Hamming distance: %d\n", hamming_distance(a, b));

    return EXIT_SUCCESS;
}