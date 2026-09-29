#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned long long countTotalSetBits(unsigned long long n) {
    unsigned long long count = 0;
    unsigned long long i = 0;
    
    for (i = 0; (1ULL << i) <= n; i++) {
        unsigned long long bit_mask = 1ULL << i;
        unsigned long long period = bit_mask << 1;
        unsigned long long full_cycles = (n + 1) / period;
        unsigned long long remainder = (n + 1) % period;
        
        count += full_cycles * bit_mask;
        if (remainder > bit_mask) {
            count += remainder - bit_mask;
        }
    }
    
    return count;
}

static unsigned long long countTotalSetBitsFrom1(unsigned long long n) {
    if (n == 0) {
        return 0;
    }
    return countTotalSetBits(n);
}

static unsigned long long countTotalUnsetBits(unsigned long long n) {
    if (n == 0) {
        return 0;
    }
    
    unsigned long long total_bits = 0;
    unsigned long long temp = n;
    
    while (temp > 0) {
        total_bits++;
        temp >>= 1;
    }
    
    unsigned long long unset_bits = 0;
    unsigned long long x;
    for (x = 1; x <= n; x++) {
        unsigned long long bits_in_x = 0;
        unsigned long long tx = x;
        while (tx > 0) {
            bits_in_x++;
            tx >>= 1;
        }
        unsigned long long set_in_x = __builtin_popcountll(x);
        unset_bits += (bits_in_x - set_in_x);
    }
    
    return unset_bits;
}

int main(void) {
    unsigned long long n;
    
    printf("Enter a number: ");
    if (scanf("%llu", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = countTotalUnsetBits(n);
    printf("Total unset bits from 1 to %llu: %llu\n", n, result);
    
    return EXIT_SUCCESS;
}