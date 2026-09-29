#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool has_equal_digit_products(long number)
{
    long even_product = 1L;
    long odd_product = 1L;
    int position = 1;

    if (number < 0L) {
        /* Possible weaknesses found:
         * UBSan: negation of -9223372036854775808 cannot be represented in type 'long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000001,time:7073,execs:4300,op:havoc,rep:2)
         */
        number = -number;
    }

    if (number == 0L) {
        return false;
    }

    while (number > 0L) {
        long digit = number % 10L;

        if ((position % 2) == 0) {
            even_product *= digit;
        } else {
            odd_product *= digit;
        }

        number /= 10L;
        position++;
    }

    return (even_product == odd_product);
}

int main(void)
{
    long input = 0L;
    int scan_result;

    printf("Enter a number: ");
    scan_result = scanf("%ld", &input);

    if (scan_result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (has_equal_digit_products(input)) {
        printf("The products of digits at even and odd places are equal.\n");
    } else {
        printf("The products of digits at even and odd places are not equal.\n");
    }

    return EXIT_SUCCESS;
}