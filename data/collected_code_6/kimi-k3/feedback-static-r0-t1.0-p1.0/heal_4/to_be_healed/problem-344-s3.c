#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>

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
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64 " %" SCNu64, &start, &end) != 2) {
        return 1;
    }
    
    if (start > end) {
        return 1;
    }
    
    uint64_t result = count_odd_factors(start, end);
    printf("%" PRIu64 "\n", result);
    
    return 0;
}