#include <stdio.h>
#include <stdlib.h>

unsigned long long cube_sum_odd(unsigned int n)
{
    unsigned long long sum = 0ULL;
    unsigned int i;

    for (i = 0U; i < n; i++) {
        unsigned long long odd = (unsigned long long)(2U * i + 1U);
        sum += odd * odd * odd;
    }

    return sum;
}

int main(void)
{
    unsigned int n;
    int result;

    printf("Enter the number of odd natural numbers: ");
    result = scanf("%u", &n);

    if (result != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n > 100000U) {
        fprintf(stderr, "Input too large.\n");
        return EXIT_FAILURE;
    }

    printf("Cube sum of first %u odd natural numbers: %llu\n", n, cube_sum_odd(n));

    return EXIT_SUCCESS;
}