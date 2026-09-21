#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t toggle_even_bits(uint32_t num) {
    return num ^ 0xAAAAAAAAu;
}

int main(void) {
    uint32_t num;
    char buffer[32];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    if (sscanf(buffer, "%" SCNu32, &num) != 1) {
        return 1;
    }
    
    printf("%" PRIu32 "\n", toggle_even_bits(num));
    
    return 0;
}