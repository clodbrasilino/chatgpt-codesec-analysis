#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int count_unset_bits(uint32_t num) {
    int count = 0;
    int total_bits = sizeof(num) * CHAR_BIT;
    
    for (int i = 0; i < total_bits; i++) {
        if (!(num & ((uint32_t)1 << i))) {
            count++;
        }
    }
    
    return count;
}

int main(void) {
    uint32_t num;
    int result;
    
    if (scanf("%u", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    result = count_unset_bits(num);
    printf("%d\n", result);
    
    return 0;
}