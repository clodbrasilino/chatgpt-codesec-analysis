#include <stdio.h>
#include <stdlib.h>

int can_be_difference_of_squares(long long n);

int can_be_difference_of_squares(long long n)
{
    long long remainder;

    if (n < 0LL) {
        n = -n;
    }

    remainder = n % 4LL;

    if (remainder == 2LL) {
        return 0;
    }

    return 1;
}

int main(void)
{
    long long number = 0LL;
    int scan_result;

    printf("Enter an integer: ");

    scan_result = scanf("%lld", &number);

    if (scan_result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (can_be_difference_of_squares(number)) {
        printf("%lld can be represented as a difference of two squares.\n", number);
    } else {
        printf("%lld cannot be represented as a difference of two squares.\n", number);
    }

    return EXIT_SUCCESS;
}