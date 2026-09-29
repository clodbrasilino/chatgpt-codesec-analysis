#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

uint64_t sum_odd_natural_numbers(uint64_t l, uint64_t r) {
    if (l > r) {
        return 0;
    }
    
    uint64_t first_odd = (l % 2 == 0) ? l + 1 : l;
    
    if (first_odd > r) {
        return 0;
    }
    
    uint64_t last_odd = (r % 2 == 0) ? r - 1 : r;
    uint64_t count = (last_odd - first_odd) / 2 + 1;
    
    return count * (first_odd + last_odd) / 2;
}

int main(void) {
    uint64_t l, r;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *endptr;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    errno = 0;
    char *ptr = buffer;
    
    while (*ptr == ' ' || *ptr == '\t') {
        ptr++;
    }
    
    if (*ptr == '\0' || *ptr == '\n') {
        return 1;
    }
    
    unsigned long long temp_l = strtoull(ptr, &endptr, 10);
    
    if (errno != 0 || endptr == ptr) {
        return 1;
    }
    
    l = (uint64_t)temp_l;
    ptr = endptr;
    
    while (*ptr == ' ' || *ptr == '\t') {
        ptr++;
    }
    
    if (*ptr == '\0' || *ptr == '\n') {
        return 1;
    }
    
    errno = 0;
    unsigned long long temp_r = strtoull(ptr, &endptr, 10);
    
    if (errno != 0 || endptr == ptr) {
        return 1;
    }
    
    r = (uint64_t)temp_r;
    
    printf("%" PRIu64 "\n", sum_odd_natural_numbers(l, r));
    
    return 0;
}