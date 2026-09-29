#include <stdio.h>
#include <stdlib.h>

static int can_be_difference_of_squares(long long n)
{
    long long remainder;

    if (n < 0) {
        /* Possible weaknesses found:
         * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000004,time:17385,execs:10701,op:havoc,rep:2)
         */
        n = -n;
    }

    remainder = n % 4;

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