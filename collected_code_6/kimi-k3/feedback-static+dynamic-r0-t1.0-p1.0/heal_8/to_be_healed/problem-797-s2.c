#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>

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
    char buffer[1024];
    char *endptr;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    errno = 0;
    l = strtoull(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer) {
        return 1;
    }
    
    while (*endptr == ' ' || *endptr == '\t') {
        endptr++;
    }
    
    errno = 0;
    r = strtoull(endptr, &endptr, 10);
    if (errno != 0 || endptr == buffer) {
        return 1;
    }
    
    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n') {
        endptr++;
    }
    
    if (*endptr != '\0') {
        return 1;
    }
    
    printf("%" PRIu64 "\n", sum_odd_natural_numbers(l, r));
    
    return 0;
}