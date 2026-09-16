#include <stdio.h>
#include <stdlib.h>

int count_total_bits(int n) {
    int count = 0;
    unsigned int temp = (unsigned int)n;
    while (temp > 0) {
        count++;
        temp >>= 1;
    }
    return count == 0 ? 1 : count;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got 2
  *  test case 1 failed: expected 4, got 8
  *  test case 2 failed: expected 17, got 28
  */

unsigned long long count_unset_bits(int n) {
    if (n <= 0) {
        return 0;
    }
    
    int total_bits = count_total_bits(n);
    unsigned long long total_positions = (unsigned long long)n * total_bits;
    unsigned long long set_bits = 0;
    
    for (int i = 0; i < total_bits; i++) {
        unsigned long long pattern_length = 1ULL << (i + 1);
        unsigned long long full_patterns = ((unsigned long long)n + 1) / pattern_length;
        unsigned long long remainder = ((unsigned long long)n + 1) % pattern_length;
        unsigned long long ones_in_full_pattern = 1ULL << i;
        
        set_bits += full_patterns * ones_in_full_pattern;
        
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
    
    for (int i = 1; i <= n; i++) {
        printf("%llu", count_unset_bits(i));
        if (i < n) {
            printf(" ");
        }
    }
    printf("\n");
    
    return EXIT_SUCCESS;
}