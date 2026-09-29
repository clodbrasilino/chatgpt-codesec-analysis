#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t star_number(uint64_t n) {
    return 6 * n * (n - 1) + 1;
}

int main(void) {
    uint64_t n;
    
    if (scanf("%" SCNu64, &n) != 1) {
        return 1;
    }
    
    if (n == 0) {
        return 1;
    }
    
    printf("%" PRIu64 "\n", star_number(n));
    
    return 0;
}