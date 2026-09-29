#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

uint64_t decagonal_number(uint64_t n) {
    if (n == 0) {
        return 0;
    }
    
    if (n > (UINT64_MAX + 3) / 4) {
        return 0;
    }
    
    uint64_t four_n_minus_3 = 4 * n - 3;
    if (n > UINT64_MAX / four_n_minus_3) {
        return 0;
    }
    
    return n * four_n_minus_3;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;
    uint64_t n;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    errno = 0;
    n = strtoull(buffer, &endptr, 10);
    
    if (errno == ERANGE || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        return 1;
    }
    
    printf("%" PRIu64 "\n", decagonal_number(n));
    
    return 0;
}