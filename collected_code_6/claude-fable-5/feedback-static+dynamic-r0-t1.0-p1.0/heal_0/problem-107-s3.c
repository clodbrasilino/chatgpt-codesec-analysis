#include <stdio.h>
#include <stdlib.h>

static int hasHexLetter(unsigned long n)
{
    while (n > 0UL) {
        unsigned long digit = n % 16UL;
        if (digit >= 10UL) {
            return 1;
        }
        n /= 16UL;
    }
    return 0;
}

static unsigned long countHexNumbers(unsigned long lower, unsigned long upper)
{
    unsigned long count = 0UL;
    unsigned long i = lower;

    while (i <= upper) {
        if (hasHexLetter(i) != 0) {
            count++;
        }
        if (i == upper) {
            break;
        }
        i++;
    }
    return count;
}

int main(void)
{
    unsigned long lower = 0UL;
    unsigned long upper = 0UL;
    unsigned long result = 0UL;

    printf("Enter lower bound: ");
    if (scanf("%lu", &lower) != 1) {
        fprintf(stderr, "Error: invalid input for lower bound\n");
        return EXIT_FAILURE;
    }

    printf("Enter upper bound: ");
    if (scanf("%lu", &upper) != 1) {
        fprintf(stderr, "Error: invalid input for upper bound\n");
        return EXIT_FAILURE;
    }

    if (lower > upper) {
        fprintf(stderr, "Error: lower bound must not exceed upper bound\n");
        return EXIT_FAILURE;
    }

    result = countHexNumbers(lower, upper);
    printf("Count of numbers with hexadecimal letters in range [%lu, %lu]: %lu\n",
           lower, upper, result);

    return EXIT_SUCCESS;
}