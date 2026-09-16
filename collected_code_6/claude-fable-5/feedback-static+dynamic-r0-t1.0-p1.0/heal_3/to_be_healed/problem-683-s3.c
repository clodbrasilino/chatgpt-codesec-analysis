#include <stdio.h>
#include <stdbool.h>
#include <math.h>

static long long integer_sqrt(long long n)
{
    /* Possible weaknesses found:
     *  Invalid argument
     *  Invalid sqrt() argument nr 1. The value is -1 but the valid values are '0.0:'. [invalidFunctionArg]
     */
    long long root = (long long)sqrt((double)n);

    while (root > 0 && root * root > n) {
        root--;
    }
    while ((root + 1) * (root + 1) <= n) {
        root++;
    }

    return root;
}

static bool is_sum_of_two_squares(long long n)
{
    /* Possible weaknesses found:
     *  Assignment 'a=0', assigned value is 0
     */
    for (long long a = 0; a * a <= n; a++) {
        /* Possible weaknesses found:
         *  remainder is assigned 'n-a*a' here.
         */
        long long remainder = n - a * a;
        /* Possible weaknesses found:
         *  Calling function 'integer_sqrt', 1st argument 'remainder' value is -1
         */
        long long b = integer_sqrt(remainder);

        if (b * b == remainder) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    long long number = 0;

    printf("Enter a non-negative integer: ");

    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return 1;
    }

    if (number < 0) {
        fprintf(stderr, "Error: number must be non-negative.\n");
        return 1;
    }

    if (is_sum_of_two_squares(number)) {
        printf("%lld can be represented as the sum of two squares.\n", number);
    } else {
        printf("%lld cannot be represented as the sum of two squares.\n", number);
    }

    return 0;
}