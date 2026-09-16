#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int digit_sum_of_power(unsigned int base, unsigned int exponent, unsigned long *result)
{
    unsigned char *digits;
    size_t capacity;
    size_t length;
    size_t i;
    unsigned int e;
    unsigned long sum;

    if (result == NULL) {
        return -1;
    }

    capacity = 16u;
    digits = malloc(capacity);
    if (digits == NULL) {
        return -1;
    }

    digits[0] = 1u;
    length = 1u;

    for (e = 0u; e < exponent; e++) {
        unsigned long carry = 0ul;

        for (i = 0u; i < length; i++) {
            unsigned long product = (unsigned long)digits[i] * (unsigned long)base + carry;
            digits[i] = (unsigned char)(product % 10ul);
            carry = product / 10ul;
        }

        while (carry > 0ul) {
            if (length >= capacity) {
                unsigned char *tmp;

                if (capacity > (SIZE_MAX / 2u)) {
                    free(digits);
                    return -1;
                }
                capacity *= 2u;
                tmp = realloc(digits, capacity);
                if (tmp == NULL) {
                    free(digits);
                    return -1;
                }
                digits = tmp;
            }
            digits[length] = (unsigned char)(carry % 10ul);
            length++;
            carry /= 10ul;
        }
    }

    sum = 0ul;
    for (i = 0u; i < length; i++) {
        sum += (unsigned long)digits[i];
    }

    free(digits);
    *result = sum;
    return 0;
}

int main(void)
{
    unsigned int base;
    unsigned int exponent;
    unsigned long sum;

    printf("Enter base: ");
    if (scanf("%u", &base) != 1) {
        fprintf(stderr, "Invalid input for base.\n");
        return EXIT_FAILURE;
    }

    printf("Enter exponent: ");
    if (scanf("%u", &exponent) != 1) {
        fprintf(stderr, "Invalid input for exponent.\n");
        return EXIT_FAILURE;
    }

    if (base > 1000000u || exponent > 100000u) {
        fprintf(stderr, "Input values too large.\n");
        return EXIT_FAILURE;
    }

    if (digit_sum_of_power(base, exponent, &sum) != 0) {
        fprintf(stderr, "Computation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Digit sum of %u^%u is %lu\n", base, exponent, sum);
    return EXIT_SUCCESS;
}