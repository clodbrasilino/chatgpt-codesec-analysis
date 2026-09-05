#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <limits.h>

uint64_t count_odd_factors(uint64_t start, uint64_t end) {
    if (start > end) {
        return 0;
    }
    
    uint64_t sqrt_end = (uint64_t)sqrt((double)end);
    while ((sqrt_end + 1) * (sqrt_end + 1) <= end) {
        sqrt_end++;
    }
    while (sqrt_end * sqrt_end > end) {
        sqrt_end--;
    }
    
    uint64_t sqrt_start_minus_one = 0;
    if (start > 0) {
        uint64_t s = start - 1;
        sqrt_start_minus_one = (uint64_t)sqrt((double)s);
        while ((sqrt_start_minus_one + 1) * (sqrt_start_minus_one + 1) <= s) {
            sqrt_start_minus_one++;
        }
        while (sqrt_start_minus_one * sqrt_start_minus_one > s) {
            sqrt_start_minus_one--;
        }
    }
    
    return sqrt_end - sqrt_start_minus_one;
}

int main(void) {
    uint64_t start, end;
    
    /* Possible weaknesses found:
     *  %llu in format string (no. 1) requires 'unsigned long long *' but the argument type is 'unsigned long *'. [invalidScanfArgType_int]
     *  %llu in format string (no. 2) requires 'unsigned long long *' but the argument type is 'unsigned long *'. [invalidScanfArgType_int]
     */
    if (scanf("%llu %llu", &start, &end) != 2) {
        return 1;
    }
    
    if (start > end) {
        return 1;
    }
    
    uint64_t result = count_odd_factors(start, end);
    /* Possible weaknesses found:
     *  %llu in format string (no. 1) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     */
    printf("%llu\n", result);
    
    return 0;
}