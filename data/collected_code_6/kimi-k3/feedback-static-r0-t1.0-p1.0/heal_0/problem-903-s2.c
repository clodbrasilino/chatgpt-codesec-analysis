#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

unsigned long long count_unset_bits(unsigned int n)
{
    unsigned long long total_unset = 0;
    unsigned int i;
    
    for (i = 1; i <= n; i++) {
        unsigned int num = i;
        unsigned int bit_count = 0;
        unsigned int temp = num;
        
        while (temp > 0) {
            bit_count++;
            temp >>= 1;
        }
        
        if (bit_count == 0) {
            bit_count = 1;
        }
        
        total_unset += bit_count - __builtin_popcount(num);
    }
    
    return total_unset;
}

int main(void)
{
    unsigned int n;
    int result;
    
    printf("Enter a positive integer: ");
    result = scanf("%u", &n);
    
    if (result != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n == 0) {
        fprintf(stderr, "Input must be greater than 0\n");
        return EXIT_FAILURE;
    }
    
    printf("Total unset bits from 1 to %u: %llu\n", n, count_unset_bits(n));
    
    return EXIT_SUCCESS;
}