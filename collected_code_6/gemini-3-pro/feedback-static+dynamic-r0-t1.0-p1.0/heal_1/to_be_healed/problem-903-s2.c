#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long count_unset_bits(unsigned long long n) {
    if (n == 0) {
        return 0;
    }
    
    unsigned long long total_bits = 0;
    unsigned long long num = n;
    int bit_length = 0;
    
    while (num > 0) {
        bit_length++;
        num >>= 1;
    }
    
    unsigned long long total_set_bits = 0;
    
    for (int i = 0; i < bit_length; i++) {
        /* Possible weaknesses found:
         * UBSan: shift exponent 64 is too large for 64-bit type 'unsigned long long' (AFL crash: id:000000,sig:06,src:000002,time:7297,execs:171,op:havoc,rep:4)
         */
        unsigned long long block_size = 1ULL << (i + 1);
        unsigned long long half_block = 1ULL << i;
        
        unsigned long long full_blocks = (n + 1) / block_size;
        total_set_bits += full_blocks * half_block;
        
        unsigned long long remainder = (n + 1) % block_size;
        if (remainder > half_block) {
            total_set_bits += remainder - half_block;
        }
    }
    
    for (unsigned long long i = 1; i <= n; i++) {
        unsigned long long temp = i;
        while (temp > 0) {
            total_bits++;
            temp >>= 1;
        }
    }
    
    return total_bits - total_set_bits;
}

int main(void) {
    unsigned long long n;
    
    if (scanf("%llu", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long unset_bits = count_unset_bits(n);
    printf("%llu\n", unset_bits);
    
    return EXIT_SUCCESS;
}