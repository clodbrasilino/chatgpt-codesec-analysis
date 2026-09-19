#include <stdio.h>
#include <stdbool.h>
#include <math.h>

static bool is_sum_of_two_squares(long long n)
{
    if (n < 0) {
        return false;
    }

    /* Possible weaknesses found:
     *  Assignment 'a=0', assigned value is 0
     */
    for (long long a = 0; a * a <= n; a++) {
        /* Possible weaknesses found:
         *  remainder is assigned 'n-a*a' here.
         */
        long long remainder = n - a * a;
        /* Possible weaknesses found:
         *  Invalid argument
         *  Invalid sqrt() argument nr 1. The value is -1 but the valid values are '0.0:'. [invalidFunctionArg]
         */
        long long b = (long long)sqrt((double)remainder);

        if (b * b == remainder) {
            return true;
        }
        if ((b + 1) * (b + 1) == remainder) {
            return true;
        }
    }

    return false;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:10358,execs:273,op:havoc,rep:1; likely memory-safety defect
  */

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