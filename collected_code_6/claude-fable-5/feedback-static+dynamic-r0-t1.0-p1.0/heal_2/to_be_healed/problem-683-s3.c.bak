#include <stdio.h>
#include <stdbool.h>
#include <math.h>

static long long integer_sqrt(long long n)
{
    if (n < 0) {
        return -1;
    }

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
     *  Assuming that condition 'n<0' is not redundant
     */
    if (n < 0) {
        return false;
    }

    /* Possible weaknesses found:
     *  Assignment 'a=0', assigned value is 0
     */
    for (long long a = 0; a * a <= n; a++) {
        /* Possible weaknesses found:
         *  Assignment 'remainder=n-a*a', assigned value is greater than -1
         */
        long long remainder = n - a * a;

        /* Possible weaknesses found:
         *  Condition 'remainder<0' is always false
         *  Condition 'remainder<0' is always false [knownConditionTrueFalse]
         */
        if (remainder < 0) {
            break;
        }

        long long b = integer_sqrt(remainder);

        if (b >= 0 && b * b == remainder) {
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