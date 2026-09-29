#include <stdio.h>
#include <stdlib.h>

unsigned long long cube_sum_even(unsigned int n)
{
    unsigned long long sum = 0;
    unsigned long long term;
    unsigned int i;

    for (i = 1; i <= n; i++) {
        term = (unsigned long long)(2U * i);
        sum += term * term * term;
    }

    return sum;
}

int main(void)
{
    unsigned int n;
    int result;

    printf("Enter the number of even natural numbers: ");
    result = scanf("%u", &n);

    if (result != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (n > 100000U) {
        fprintf(stderr, "Error: input too large\n");
        return EXIT_FAILURE;
    }

    printf("Cube sum of first %u even natural numbers: %llu\n", n, cube_sum_even(n));

    return EXIT_SUCCESS;
}