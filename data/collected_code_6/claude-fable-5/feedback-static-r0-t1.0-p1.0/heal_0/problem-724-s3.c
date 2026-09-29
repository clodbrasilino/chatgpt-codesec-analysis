#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int digit_power_sum(unsigned int base, unsigned int exponent)
{
    size_t capacity = 16;
    size_t length = 1;
    size_t i;
    unsigned int e;
    unsigned char *digits;
    unsigned long carry;
    unsigned long product;
    int sum;

    digits = malloc(capacity);
    if (digits == NULL) {
        return -1;
    }

    digits[0] = 1;

    for (e = 0; e < exponent; e++) {
        carry = 0;
        for (i = 0; i < length; i++) {
            product = (unsigned long)digits[i] * base + carry;
            digits[i] = (unsigned char)(product % 10);
            carry = product / 10;
        }
        while (carry > 0) {
            if (length >= capacity) {
                size_t new_capacity = capacity * 2;
                unsigned char *tmp = realloc(digits, new_capacity);
                if (tmp == NULL) {
                    free(digits);
                    return -1;
                }
                digits = tmp;
                capacity = new_capacity;
            }
            digits[length] = (unsigned char)(carry % 10);
            carry /= 10;
            length++;
        }
    }

    sum = 0;
    for (i = 0; i < length; i++) {
        sum += digits[i];
    }

    free(digits);
    return sum;
}

int main(void)
{
    unsigned int base;
    unsigned int exponent;
    int result;

    printf("Enter base: ");
    if (scanf("%u", &base) != 1) {
        fprintf(stderr, "Invalid input for base\n");
        return EXIT_FAILURE;
    }

    printf("Enter exponent: ");
    if (scanf("%u", &exponent) != 1) {
        fprintf(stderr, "Invalid input for exponent\n");
        return EXIT_FAILURE;
    }

    result = digit_power_sum(base, exponent);
    if (result < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Sum of digits of %u^%u is %d\n", base, exponent, result);
    return EXIT_SUCCESS;
}