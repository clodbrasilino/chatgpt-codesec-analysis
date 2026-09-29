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
    char buffer[32];
    char *endptr;
    uint64_t n;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    errno = 0;
    n = strtoull(buffer, &endptr, 10);
    
    if (errno == ERANGE || endptr == buffer) {
        return 1;
    }
    
    printf("%" PRIu64 "\n", decagonal_number(n));
    
    return 0;
}