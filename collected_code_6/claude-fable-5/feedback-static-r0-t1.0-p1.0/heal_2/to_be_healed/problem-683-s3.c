#include <stdio.h>
#include <stdbool.h>
#include <math.h>

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
         *  Condition 'remainder<0' is always false [knownConditionTrueFalse]
         *  Condition 'remainder<0' is always false
         */
        if (remainder < 0) {
            continue;
        }

        long long b = (long long)sqrt((double)remainder);

        if (b > 0 && b * b > remainder) {
            b--;
        }

        if (b * b == remainder) {
            return true;
        }
        if ((b + 1) * (b + 1) == remainder) {
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