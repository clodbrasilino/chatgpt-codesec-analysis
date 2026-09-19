#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 10000

int sum_of_digits_power(int base, int exponent)
{
    int *digits = NULL;
    int num_digits = 1;
    int sum = 0;
    int i, j, product;

    if (base < 0 || exponent < 0) {
        return -1;
    }

    if (base == 0 && exponent == 0) {
        return -1;
    }

    digits = (int *)calloc(MAX_DIGITS, sizeof(int));
    if (digits == NULL) {
        return -1;
    }

    digits[0] = 1;

    for (i = 0; i < exponent; i++) {
        int carry = 0;
        for (j = 0; j < num_digits; j++) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 9 * 298954296 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:4935,execs:641,op:havoc,rep:1)
             * UBSan: signed integer overflow: 2092680072 + 121573243 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:4935,execs:641,op:havoc,rep:1)
             * UBSan: signed integer overflow: 8 * 888888888 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000002,time:10554,execs:1898,op:havoc,rep:2)
             */
            product = digits[j] * base + carry;
            digits[j] = product % 10;
            carry = product / 10;
        }
        while (carry > 0) {
            if (num_digits >= MAX_DIGITS) {
                free(digits);
                return -1;
            }
            digits[num_digits] = carry % 10;
            carry /= 10;
            num_digits++;
        }
    }

    for (i = 0; i < num_digits; i++) {
        sum += digits[i];
    }

    free(digits);
    return sum;
}

int main(void)
{
    int base, exponent, result;

    if (scanf("%d %d", &base, &exponent) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = sum_of_digits_power(base, exponent);

    if (result < 0) {
        fprintf(stderr, "Error calculating result\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}