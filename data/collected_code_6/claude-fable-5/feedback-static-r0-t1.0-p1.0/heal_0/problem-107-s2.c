#include <stdio.h>
#include <stdlib.h>

static int contains_hex_letter(unsigned long n)
{
    if (n == 0UL) {
        return 0;
    }
    while (n > 0UL) {
        if ((n % 16UL) >= 10UL) {
            return 1;
        }
        n /= 16UL;
    }
    return 0;
}

static unsigned long count_hex_numbers(unsigned long low, unsigned long high)
{
    unsigned long count = 0UL;
    unsigned long i = low;

    for (;;) {
        if (contains_hex_letter(i)) {
            count++;
        }
        if (i == high) {
            break;
        }
        i++;
    }
    return count;
}

int main(void)
{
    unsigned long low = 0UL;
    unsigned long high = 0UL;
    unsigned long result = 0UL;

    printf("Enter lower bound: ");
    if (scanf("%lu", &low) != 1) {
        fprintf(stderr, "Invalid input for lower bound\n");
        return EXIT_FAILURE;
    }

    printf("Enter upper bound: ");
    if (scanf("%lu", &high) != 1) {
        fprintf(stderr, "Invalid input for upper bound\n");
        return EXIT_FAILURE;
    }

    if (low > high) {
        fprintf(stderr, "Lower bound must not exceed upper bound\n");
        return EXIT_FAILURE;
    }

    result = count_hex_numbers(low, high);

    if (printf("Count of numbers containing hexadecimal letters in range [%lu, %lu]: %lu\n",
               low, high, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}