#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_of_odd_squares(unsigned int n)
{
    unsigned long long sum = 0ULL;
    /* Possible weaknesses found:
     *  The scope of the variable 'odd' can be reduced. [variableScope]
     */
    unsigned long long odd;
    unsigned int i;

    for (i = 0U; i < n; i++) {
        odd = (2ULL * (unsigned long long)i) + 1ULL;
        sum += odd * odd;
    }

    return sum;
}

int main(void)
{
    unsigned int n = 0U;
    int result;

    printf("Enter the number of odd natural numbers: ");
    result = scanf("%u", &n);

    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n > 1000000U) {
        fprintf(stderr, "Error: input too large.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of squares of first %u odd natural numbers: %llu\n",
           n, sum_of_odd_squares(n));

    return EXIT_SUCCESS;
}