#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void multiply_by_base(int *digits, int *digit_count, int base, int capacity) {
    int carry = 0;
    for (int i = 0; i < *digit_count; ++i) {
        long long product = (long long)digits[i] * base + carry;
        digits[i] = product % 10;
        carry = product / 10;
    }
    while (carry > 0 && *digit_count < capacity) {
        digits[*digit_count] = carry % 10;
        carry /= 10;
        (*digit_count)++;
    }
    if (carry > 0) {
        fprintf(stderr, "Buffer overflow prevented\n");
        exit(EXIT_FAILURE);
    }
}

int sum_of_digits_base_power(int base, int exponent) {
    if (base < 0 || exponent < 0) {
        fprintf(stderr, "Invalid input: base and exponent must be non-negative\n");
        return -1;
    }
    if (base == 0 && exponent == 0) {
        return 1;
    }
    if (base == 0) {
        return 0;
    }
    if (exponent == 0) {
        return 1;
    }

    int capacity = 1024;
    int *digits = calloc((size_t)capacity, sizeof(int));
    if (digits == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }

    digits[0] = 1;
    int digit_count = 1;

    for (int i = 0; i < exponent; ++i) {
        if (digit_count > capacity / 2) {
            capacity *= 2;
            int *new_digits = realloc(digits, (size_t)capacity * sizeof(int));
            if (new_digits == NULL) {
                free(digits);
                fprintf(stderr, "Memory reallocation failed\n");
                return -1;
            }
            digits = new_digits;
            memset(digits + digit_count, 0, (size_t)(capacity - digit_count) * sizeof(int));
        }
        multiply_by_base(digits, &digit_count, base, capacity);
    }

    int sum = 0;
    for (int i = 0; i < digit_count; ++i) {
        sum += digits[i];
    }

    free(digits);
    return sum;
}

int main(void) {
    int base, exponent;
    
    printf("Enter base: ");
    if (scanf("%d", &base) != 1) {
        fprintf(stderr, "Invalid input for base\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter exponent: ");
    if (scanf("%d", &exponent) != 1) {
        fprintf(stderr, "Invalid input for exponent\n");
        return EXIT_FAILURE;
    }

    int result = sum_of_digits_base_power(base, exponent);
    if (result != -1) {
        printf("Sum of digits: %d\n", result);
    }

    return EXIT_SUCCESS;
}