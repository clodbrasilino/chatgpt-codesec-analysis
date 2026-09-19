#include <stdio.h>
#include <stdlib.h>

int digit_sum_difference(long long number);

int digit_sum_difference(long long number)
{
    int even_sum = 0;
    int odd_sum = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'digit' can be reduced. [variableScope]
     */
    int digit;

    if (number < 0) {
        /* Possible weaknesses found:
         * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000013,time:22498,execs:13469,op:havoc,rep:2)
         */
        number = -number;
    }

    if (number == 0) {
        return 0;
    }

    while (number > 0) {
        digit = (int)(number % 10);
        if ((digit % 2) == 0) {
            even_sum += digit;
        } else {
            odd_sum += digit;
        }
        number /= 10;
    }

    return even_sum - odd_sum;
}

int main(void)
{
    long long input = 0;
    int result;

    printf("Enter an integer: ");
    if (scanf("%lld", &input) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    result = digit_sum_difference(input);
    printf("Difference between sum of even and odd digits: %d\n", result);

    return EXIT_SUCCESS;
}