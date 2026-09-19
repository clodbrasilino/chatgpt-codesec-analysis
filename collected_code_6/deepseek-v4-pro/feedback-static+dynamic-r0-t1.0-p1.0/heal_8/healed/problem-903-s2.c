#include <stdio.h>
#include <stdlib.h>

unsigned long long count_set_bits(int n) {
    if (n <= 0) {
        return 0;
    }
    
    unsigned long long set_bits = 0;
    int i = 0;
    
    while ((1LL << i) <= n) {
        unsigned long long pattern_length = 1ULL << (i + 1);
        unsigned long long full_patterns = (n + 1ULL) / pattern_length;
        unsigned long long remainder = (n + 1ULL) % pattern_length;
        unsigned long long ones_in_full_pattern = 1ULL << i;
        
        set_bits += full_patterns * ones_in_full_pattern;
        
        if (remainder > ones_in_full_pattern) {
            set_bits += remainder - ones_in_full_pattern;
        }
        
        i++;
    }
    
    return set_bits;
}

unsigned long long count_unset_bits(int n) {
    if (n <= 0) {
        return 0;
    }
    
    unsigned long long total_set_bits = count_set_bits(n);
    
    int total_bits = 0;
    int temp = n;
    while (temp > 0) {
        total_bits++;
        temp >>= 1;
    }
    if (total_bits == 0) {
        total_bits = 1;
    }
    
    unsigned long long total_positions = 0;
    for (int num = 1; num <= n; num++) {
        int bits = 0;
        int temp_num = num;
        while (temp_num > 0) {
            bits++;
            temp_num >>= 1;
        }
        if (bits == 0) bits = 1;
        total_positions += bits;
    }
    
    return total_positions - total_set_bits;
}

int main(void) {
    int n;
    
    printf("Enter a number: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Number must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    printf("Total unset bits from 1 to %d: %llu\n", n, count_unset_bits(n));
    
    return EXIT_SUCCESS;
}