#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long sum_of_fourth_powers(unsigned int n)
{
    unsigned long long sum = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'fourth' can be reduced. [variableScope]
     */
    unsigned long long i, fourth;
    
    for (i = 1; i <= n; i++) {
        if (i > ULLONG_MAX / i) {
            errno = ERANGE;
            return 0;
        }
        fourth = i * i;
        if (fourth > ULLONG_MAX / i) {
            errno = ERANGE;
            return 0;
        }
        fourth = fourth * i;
        if (fourth > ULLONG_MAX / i) {
            errno = ERANGE;
            return 0;
        }
        fourth = fourth * i;
        if (sum > ULLONG_MAX - fourth) {
            errno = ERANGE;
            return 0;
        }
        sum += fourth;
    }
    
    return sum;
}

int main(void)
{
    unsigned int n;
    unsigned long long result;
    
    printf("Enter a positive integer: ");
    
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n == 0) {
        fprintf(stderr, "Input must be positive\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    result = sum_of_fourth_powers(n);
    
    if (errno == ERANGE) {
        fprintf(stderr, "Overflow occurred during calculation\n");
        return EXIT_FAILURE;
    }
    
    printf("Sum of fourth powers of first %u natural numbers: %llu\n", n, result);
    
    return EXIT_SUCCESS;
}