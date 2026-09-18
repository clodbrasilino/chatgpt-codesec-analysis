#include <stdio.h>
#include <stdlib.h>

int digit_sum_difference(long number)
{
    int even_sum = 0;
    int odd_sum = 0;
    unsigned long n;

    if (number < 0) {
        n = (unsigned long)(-(number + 1)) + 1UL;
    } else {
        n = (unsigned long)number;
    }

    if (n == 0UL) {
        return 0;
    }

    while (n > 0UL) {
        int digit = (int)(n % 10UL);
        if (digit % 2 == 0) {
            even_sum += digit;
        } else {
            odd_sum += digit;
        }
        n /= 10UL;
    }

    return even_sum - odd_sum;
}

int main(void)
{
    long number = 0;
    int result = 0;

    printf("Enter an integer: ");

    if (scanf("%ld", &number) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    result = digit_sum_difference(number);

    printf("Difference between sum of even and odd digits: %d\n", result);

    return EXIT_SUCCESS;
}