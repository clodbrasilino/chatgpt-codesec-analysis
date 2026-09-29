#include <stdio.h>
#include <stdlib.h>

static int can_be_difference_of_squares(long long n)
{
    unsigned long long magnitude;
    unsigned long long remainder;

    if (n < 0) {
        magnitude = -(unsigned long long)n;
    } else {
        magnitude = (unsigned long long)n;
    }

    remainder = magnitude % 4;

    if (remainder == 2) {
        return 0;
    }

    return 1;
}

int main(void)
{
    long long number = 0;
    int scan_result;

    printf("Enter a number: ");

    scan_result = scanf("%lld", &number);

    if (scan_result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (can_be_difference_of_squares(number)) {
        printf("%lld can be represented as difference of two squares.\n", number);
    } else {
        printf("%lld cannot be represented as difference of two squares.\n", number);
    }

    return EXIT_SUCCESS;
}