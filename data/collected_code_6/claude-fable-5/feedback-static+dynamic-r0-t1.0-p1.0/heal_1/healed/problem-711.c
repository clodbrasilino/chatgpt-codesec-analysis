#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

bool has_equal_digit_products(long number)
{
    unsigned long magnitude;
    unsigned long even_product = 1UL;
    unsigned long odd_product = 1UL;
    int position = 1;

    if (number < 0L) {
        magnitude = (unsigned long)(-(number + 1L)) + 1UL;
    } else {
        magnitude = (unsigned long)number;
    }

    if (magnitude == 0UL) {
        return false;
    }

    while (magnitude > 0UL) {
        unsigned long digit = magnitude % 10UL;

        if ((position % 2) == 0) {
            even_product *= digit;
        } else {
            odd_product *= digit;
        }

        magnitude /= 10UL;
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