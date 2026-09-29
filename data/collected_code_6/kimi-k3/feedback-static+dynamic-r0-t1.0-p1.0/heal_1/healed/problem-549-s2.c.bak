#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

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
    
    if (scanf("%" SCNu32, &n) != 1) {
        return 1;
    }
    
    result = sum_fifth_power_odd(n);
    printf("%" PRIu64 "\n", result);
    
    return 0;
}