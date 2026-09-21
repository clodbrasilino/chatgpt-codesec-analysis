#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 0, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  *  test case 0 failed: expected 6, got <no output>
  */

int count_hexadecimal_numbers(unsigned long long start, unsigned long long end) {
    if (start > end) {
        return -1;
    }
    
    if (start == 0 && end == 0) {
        return 1;
    }
    
    unsigned long long max = end;
    unsigned long long min = (start == 0) ? 1 : start;
    
    if (min > max) {
        return (start == 0) ? 1 : 0;
    }
    
    unsigned long long max_bits = 64 - __builtin_clzll(max);
    unsigned long long min_bits = 64 - __builtin_clzll(min);
    unsigned long long max_digits = (max_bits + 3) / 4;
    unsigned long long min_digits = (min_bits + 3) / 4;
    
    unsigned long long total = 0;
    
    if (min_digits == max_digits) {
        total = (max - min + 1) * min_digits;
    } else {
        unsigned long long first_boundary = 1ULL << (min_digits * 4);
        total += (first_boundary - min) * min_digits;
        
        for (unsigned long long d = min_digits + 1; d < max_digits; d++) {
            unsigned long long low = 1ULL << ((d - 1) * 4);
            unsigned long long high = 1ULL << (d * 4);
            total += (high - low) * d;
        }
        
        unsigned long long last_start = 1ULL << ((max_digits - 1) * 4);
        total += (max - last_start + 1) * max_digits;
    }
    
    if (start == 0) {
        total += 1;
    }
    
    return (int)total;
}

int main(void) {
    unsigned long long start, end;
    int result;

    if (scanf("%llu", &start) != 1) {
        return EXIT_FAILURE;
    }

    if (scanf("%llu", &end) != 1) {
        return EXIT_FAILURE;
    }

    result = count_hexadecimal_numbers(start, end);

    if (result < 0) {
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}