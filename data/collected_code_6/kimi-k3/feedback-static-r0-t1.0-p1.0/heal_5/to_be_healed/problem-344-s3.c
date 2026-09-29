#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *ptr;
    char *endptr;
    uint64_t start, end;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    errno = 0;
    ptr = buffer;
    start = strtoull(ptr, &endptr, 10);
    if (errno != 0 || endptr == ptr) {
        return 1;
    }
    
    ptr = endptr;
    while (*ptr == ' ' || *ptr == '\t') {
        ptr++;
    }
    
    errno = 0;
    end = strtoull(ptr, &endptr, 10);
    if (errno != 0 || endptr == ptr) {
        return 1;
    }
    
    if (start > end) {
        return 1;
    }
    
    uint64_t result = count_odd_factors(start, end);
    printf("%" PRIu64 "\n", result);
    
    return 0;
}