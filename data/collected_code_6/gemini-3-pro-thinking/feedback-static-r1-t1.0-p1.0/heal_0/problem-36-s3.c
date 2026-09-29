#include <stdio.h>
#include <stdlib.h>

unsigned long long modular_pow(unsigned long long base, unsigned long long exponent, unsigned long long modulus) {
    if (modulus == 1) {
        return 0;
    }
    unsigned long long result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if ((exponent & 1) == 1) {
            result = (result * base) % modulus;
        }
        exponent >>= 1;
        base = (base * base) % modulus;
    }
    return result;
}

int find_nth_digit(unsigned int numerator, unsigned int denominator, unsigned int n) {
    if (denominator == 0 || n == 0) {
        return -1;
    }
    unsigned long long num = (unsigned long long)numerator % denominator;
    if (num == 0) {
        return 0;
    }
    unsigned long long rem = modular_pow(10, (unsigned long long)n - 1, denominator);
    rem = (rem * num) % denominator;
    return (int)((rem * 10) / denominator);
}

int main(void) {
    unsigned int numerator = 1;
    unsigned int denominator = 7;
    unsigned int n = 3;

    int digit = find_nth_digit(numerator, denominator, n);

    if (digit >= 0) {
        printf("%d\n", digit);
    } else {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}