#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 10000

int sum_of_digits_power(int base, int exponent) {
    if (base < 0 || exponent < 0) {
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
    
    int digits[MAX_DIGITS];
    int num_digits = 1;
    digits[0] = 1;
    
    for (int i = 0; i < exponent; i++) {
        int carry = 0;
        for (int j = 0; j < num_digits; j++) {
            int product = digits[j] * base + carry;
            digits[j] = product % 10;
            carry = product / 10;
        }
        while (carry > 0) {
            if (num_digits >= MAX_DIGITS) {
                return -1;
            }
            digits[num_digits] = carry % 10;
            carry /= 10;
            num_digits++;
        }
    }
    
    int sum = 0;
    for (int i = 0; i < num_digits; i++) {
        sum += digits[i];
    }
    
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
    
    int result = sum_of_digits_power(base, exponent);
    
    if (result < 0) {
        fprintf(stderr, "Error: Invalid input or result too large\n");
        return EXIT_FAILURE;
    }
    
    printf("Sum of digits of %d^%d = %d\n", base, exponent, result);
    
    return EXIT_SUCCESS;
}