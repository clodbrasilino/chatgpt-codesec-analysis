#include <stdio.h>
#include <math.h>
#include <stdint.h>

uint64_t power_digits_sum(uint64_t base, uint8_t power) {
    uint64_t result = 1;
    while (power > 0) {
        result *= base;
        --power;
    }

    uint64_t sum = 0;
    while (result > 0) {
        sum += result % 10;
        result /= 10;
    }
    return sum;
}

int main() {
    uint64_t base = 2;
    uint8_t power = 15;
    uint64_t sum = power_digits_sum(base, power);
    printf("Sum of digits: %llu\n", sum);
    return 0;
}