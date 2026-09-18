#include <stdint.h>
#include <stdio.h>

uint64_t calculate_mod_pow(uint64_t base, uint64_t exponent, uint64_t modulus) {
    uint64_t result = 1;
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

int32_t find_nth_digit(int32_t numerator, int32_t denominator, int32_t n) {
    if (denominator == 0 || n <= 0) {
        return -1;
    }

    uint64_t u_num = (uint64_t)(numerator < 0 ? -(int64_t)numerator : numerator);
    uint64_t u_den = (uint64_t)(denominator < 0 ? -(int64_t)denominator : denominator);
    uint64_t u_n = (uint64_t)n;

    u_num = u_num % u_den;
    if (u_num == 0) {
        return 0;
    }

    uint64_t remainder_factor = calculate_mod_pow(10, u_n - 1, u_den);
    uint64_t current_remainder = (u_num * remainder_factor) % u_den;
    uint32_t digit = (uint32_t)((current_remainder * 10) / u_den);

    return (int32_t)digit;
}

int main(void) {
    int32_t numerator = 1;
    int32_t denominator = 7;
    int32_t n = 100;
    
    int32_t digit = find_nth_digit(numerator, denominator, n);
    
    if (digit >= 0) {
        printf("%d\n", digit);
    } else {
        printf("-1\n");
    }
    
    return 0;
}