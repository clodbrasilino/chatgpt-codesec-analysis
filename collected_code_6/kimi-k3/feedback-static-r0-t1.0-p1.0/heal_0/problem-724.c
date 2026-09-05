#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculate_digit_sum(int base, int power) {
    if (power < 0 || base < 0) {
        return -1;
    }
    
    if (power == 0) {
        return 1;
    }
    
    if (base == 0) {
        return 0;
    }
    
    size_t max_digits = (size_t)(power * 10) + 1;
    int *digits = (int *)calloc(max_digits, sizeof(int));
    if (digits == NULL) {
        return -1;
    }
    
    digits[0] = 1;
    size_t current_length = 1;
    
    for (int p = 0; p < power; p++) {
        int carry = 0;
        for (size_t i = 0; i < current_length; i++) {
            int product = digits[i] * base + carry;
            digits[i] = product % 10;
            carry = product / 10;
        }
        
        while (carry > 0) {
            if (current_length >= max_digits) {
                free(digits);
                return -1;
            }
            digits[current_length] = carry % 10;
            carry /= 10;
            current_length++;
        }
    }
    
    long long sum = 0;
    for (size_t i = 0; i < current_length; i++) {
        sum += digits[i];
    }
    
    free(digits);
    return (int)sum;
}

int main(void) {
    int base = 2;
    int power = 15;
    
    int result = calculate_digit_sum(base, power);
    
    if (result >= 0) {
        printf("%d\n", result);
    } else {
        fprintf(stderr, "Error: Invalid input or memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}