#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

uint64_t sum_fifth_power_odd(uint32_t n) {
    uint64_t sum = 0;
    uint32_t i;
    
    for (i = 0; i < n; i++) {
        uint64_t odd = 2ULL * i + 1ULL;
        uint64_t power = odd * odd * odd * odd * odd;
        
        if (UINT64_MAX - sum < power) {
            return UINT64_MAX;
        }
        sum += power;
    }
    
    return sum;
}

int main(void) {
    uint32_t n;
    uint64_t result;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;
    unsigned long temp;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    errno = 0;
    temp = strtoul(buffer, &endptr, 10);
    
    if (endptr == buffer || errno == ERANGE || temp > UINT32_MAX) {
        return 1;
    }
    
    n = (uint32_t)temp;
    
    result = sum_fifth_power_odd(n);
    printf("%" PRIu64 "\n", result);
    
    return 0;
}