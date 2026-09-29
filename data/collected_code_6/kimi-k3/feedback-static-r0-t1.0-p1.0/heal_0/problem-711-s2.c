#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int check_digit_product(long long num) {
    long long even_product = 1;
    long long odd_product = 1;
    int position = 1;
    int has_even = 0;
    int has_odd = 0;
    int digit;

    if (num == 0) {
        return 1;
    }

    if (num == LLONG_MIN) {
        return 0;
    }

    if (num < 0) {
        num = -num;
    }

    while (num > 0) {
        digit = (int)(num % 10);
        if (position % 2 == 0) {
            even_product *= digit;
            has_even = 1;
        } else {
            odd_product *= digit;
            has_odd = 1;
        }
        num /= 10;
        position++;
    }

    if (!has_even) {
        even_product = 0;
    }
    if (!has_odd) {
        odd_product = 0;
    }

    return (even_product == odd_product);
}

int main(void) {
    long long num;
    int result;

    printf("Enter a number: ");
    if (scanf("%lld", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    result = check_digit_product(num);
    if (result) {
        printf("Product of digits at even and odd places is equal\n");
    } else {
        printf("Product of digits at even and odd places is not equal\n");
    }

    return 0;
}