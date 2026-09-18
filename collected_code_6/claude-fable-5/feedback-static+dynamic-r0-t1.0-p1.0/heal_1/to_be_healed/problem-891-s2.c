#include <stdio.h>
#include <stdlib.h>

static int count_digits(long long n)
{
    int count = 1;

    if (n < 0) {
        /* Possible weaknesses found:
         * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000002,time:27933,execs:16853,op:havoc,rep:2)
         */
        n = -n;
    }

    while (n >= 10) {
        n /= 10;
        count++;
    }

    return count;
}

static int same_digit_count(long long a, long long b)
{
    return count_digits(a) == count_digits(b);
}

int main(void)
{
    long long a;
    long long b;

    printf("Enter first number: ");
    if (scanf("%lld", &a) != 1) {
        fprintf(stderr, "Invalid input for first number\n");
        return EXIT_FAILURE;
    }

    printf("Enter second number: ");
    if (scanf("%lld", &b) != 1) {
        fprintf(stderr, "Invalid input for second number\n");
        return EXIT_FAILURE;
    }

    if (same_digit_count(a, b)) {
        printf("The numbers %lld and %lld have the same number of digits.\n", a, b);
    } else {
        printf("The numbers %lld and %lld do not have the same number of digits.\n", a, b);
    }

    return EXIT_SUCCESS;
}