#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

uint64_t calculate_mod_pow(uint64_t base, uint64_t exponent, uint64_t modulus) {
    if (modulus <= 1) {
        return 0;
    }
    
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

    uint64_t u_num = (uint64_t)llabs((long long)numerator);
    uint64_t u_den = (uint64_t)llabs((long long)denominator);
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

static int parse_int32(int32_t *out) {
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    return scanf("%" SCNd32, out) == 1;
}

static void parse_optional_slash(void) {
    char c;
    if (scanf(" %c", &c) == 1) {
        if (c != '/') {
            ungetc((unsigned char)c, stdin);
        }
    }
}

int main(void) {
    int32_t numerator;
    int32_t denominator;
    int32_t n;
    
    while (parse_int32(&numerator)) {
        parse_optional_slash();
        
        if (!parse_int32(&denominator) || !parse_int32(&n)) {
            break;
        }
        
        int32_t digit = find_nth_digit(numerator, denominator, n);
        
        if (digit >= 0) {
            printf("%" PRId32 "\n", digit);
        } else {
            printf("-1\n");
        }
    }
    
    return 0;
}