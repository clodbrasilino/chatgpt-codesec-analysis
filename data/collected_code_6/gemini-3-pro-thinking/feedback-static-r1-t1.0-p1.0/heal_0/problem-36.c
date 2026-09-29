#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int8_t find_nth_digit(uint64_t numerator, uint64_t denominator, uint64_t n);

int8_t find_nth_digit(uint64_t numerator, uint64_t denominator, uint64_t n) {
    if (denominator == 0 || n == 0) {
        return -1;
    }

    uint64_t remainder = numerator % denominator;
    uint64_t digit = 0;

    for (uint64_t i = 0; i < n; i++) {
        remainder *= 10;
        digit = remainder / denominator;
        remainder = remainder % denominator;
    }

    return (int8_t)digit;
}

int main(void) {
    uint64_t numerator = 1;
    uint64_t denominator = 7;
    uint64_t n = 3;

    int8_t result = find_nth_digit(numerator, denominator, n);

    if (result != -1) {
        printf("%d\n", result);
    } else {
        fprintf(stderr, "Invalid input parameters\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}