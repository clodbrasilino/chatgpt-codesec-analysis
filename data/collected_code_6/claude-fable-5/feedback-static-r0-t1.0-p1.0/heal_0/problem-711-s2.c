#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool has_equal_digit_products(long number)
{
    long even_product = 1;
    long odd_product = 1;
    int position = 1;

    if (number < 0) {
        number = -number;
    }

    if (number == 0) {
        return false;
    }

    while (number > 0) {
        int digit = (int)(number % 10);
        if ((position % 2) == 0) {
            even_product *= digit;
        } else {
            odd_product *= digit;
        }
        number /= 10;
        position++;
    }

    return even_product == odd_product;
}

int main(void)
{
    long number = 0;

    printf("Enter a number: ");
    if (scanf("%ld", &number) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (has_equal_digit_products(number)) {
        printf("The products of digits at even and odd places are equal.\n");
    } else {
        printf("The products of digits at even and odd places are not equal.\n");
    }

    return EXIT_SUCCESS;
}