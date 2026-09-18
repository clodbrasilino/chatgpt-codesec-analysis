#include <stdio.h>
#include <stdlib.h>

int nth_digit(long long numerator, long long denominator, long long n, int *digit)
{
    long long remainder;
    long long i;

    if (digit == NULL) {
        return -1;
    }

    if (denominator == 0) {
        return -1;
    }

    if (n < 1) {
        return -1;
    }

    if (numerator < 0) {
        /* Possible weaknesses found:
         * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000002,sig:06,src:000016,time:47237,execs:16992,op:havoc,rep:3)
         */
        numerator = -numerator;
    }

    if (denominator < 0) {
        /* Possible weaknesses found:
         * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000016,time:27568,execs:13321,op:havoc,rep:1)
         */
        denominator = -denominator;
    }

    if (numerator >= denominator) {
        return -1;
    }

    remainder = numerator % denominator;

    for (i = 0; i < n - 1; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 3000000000000000000 * 10 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000009,time:30230,execs:15033,op:havoc,rep:2)
         */
        remainder = (remainder * 10) % denominator;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 6640025486929952768 * 10 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000009,time:30230,execs:15033,op:havoc,rep:2)
     */
    *digit = (int)((remainder * 10) / denominator);

    return 0;
}

int main(void)
{
    long long numerator;
    long long denominator;
    long long n;
    int digit;
    int result;

    printf("Enter numerator: ");
    if (scanf("%lld", &numerator) != 1) {
        fprintf(stderr, "Invalid input for numerator.\n");
        return EXIT_FAILURE;
    }

    printf("Enter denominator: ");
    if (scanf("%lld", &denominator) != 1) {
        fprintf(stderr, "Invalid input for denominator.\n");
        return EXIT_FAILURE;
    }

    printf("Enter n: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input for n.\n");
        return EXIT_FAILURE;
    }

    result = nth_digit(numerator, denominator, n, &digit);

    if (result != 0) {
        fprintf(stderr, "Error: invalid arguments (denominator must be nonzero, n >= 1, and fraction must be proper).\n");
        return EXIT_FAILURE;
    }

    printf("The digit at position %lld is: %d\n", n, digit);

    return EXIT_SUCCESS;
}