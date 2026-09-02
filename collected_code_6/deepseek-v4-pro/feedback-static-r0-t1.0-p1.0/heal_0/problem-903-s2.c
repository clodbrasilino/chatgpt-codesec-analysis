#include <stdio.h>
#include <stdlib.h>

int count_total_bits(int n) {
    int count = 0;
    int temp = n;
    while (temp > 0) {
        count++;
        temp >>= 1;
    }
    return count;
}

unsigned long long count_unset_bits(int n) {
    if (n <= 0) {
        return 0;
    }
    
    int total_bits = count_total_bits(n);
    unsigned long long total_positions = (unsigned long long)n * total_bits;
    unsigned long long set_bits = 0;
    
    for (int i = 0; i < total_bits; i++) {
        int pattern_length = 1 << (i + 1);
        int full_patterns = (n + 1) / pattern_length;
        int remainder = (n + 1) % pattern_length;
        int ones_in_full_pattern = 1 << i;
        
        set_bits += (unsigned long long)full_patterns * ones_in_full_pattern;
        
        if (remainder > ones_in_full_pattern) {
            set_bits += remainder - ones_in_full_pattern;
        }
    }
    
    return total_positions - set_bits;
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