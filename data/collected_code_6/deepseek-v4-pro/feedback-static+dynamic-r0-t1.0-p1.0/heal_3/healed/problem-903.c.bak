#include <stdio.h>
#include <limits.h>

unsigned long long count_total_unset_bits(unsigned long long n) {
    if (n == 0) return 0;
    
    unsigned long long result = 0;
    int total_bits = sizeof(unsigned long long) * CHAR_BIT;
    
    for (int bit_position = 0; bit_position < total_bits; bit_position++) {
        unsigned long long bit_mask = 1ULL << bit_position;
        
        if (bit_mask > n) {
            break;
        }
        
        unsigned long long cycle_length = bit_mask << 1;
        
        unsigned long long total_numbers = n + 1;
        unsigned long long full_cycles = total_numbers / cycle_length;
        unsigned long long remainder = total_numbers % cycle_length;
        
        unsigned long long total_set_bits = full_cycles * bit_mask;
        if (remainder > bit_mask) {
            total_set_bits += remainder - bit_mask;
        }
        
        result += total_numbers - total_set_bits;
    }
    
    return result;
}

int main(void) {
    unsigned long long n;
    
    printf("Enter a number: ");
    if (scanf("%llu", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    unsigned long long result = count_total_unset_bits(n);
    printf("Total unset bits from 1 to %llu: %llu\n", n, result);
    
    return 0;
}