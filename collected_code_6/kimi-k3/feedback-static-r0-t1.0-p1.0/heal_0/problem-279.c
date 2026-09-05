#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t decagonal_number(uint64_t n) {
    return n * (4 * n - 3);
}

int main(void) {
    uint64_t n;
    
    if (scanf("%" SCNu64, &n) != 1) {
        return 1;
    }
    
    printf("%" PRIu64 "\n", decagonal_number(n));
    
    return 0;
}