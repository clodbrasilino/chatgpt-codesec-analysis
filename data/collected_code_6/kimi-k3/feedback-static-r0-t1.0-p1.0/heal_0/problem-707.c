#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned int countSetBits(unsigned int n)
{
    unsigned int count = 0;
    unsigned int i;
    
    for (i = 1; i <= n; i++) {
        unsigned int num = i;
        while (num) {
            count += num & 1;
            num >>= 1;
        }
    }
    
    return count;
}

int main(void)
{
    unsigned int n;
    int result;
    
    printf("Enter a positive integer: ");
    result = scanf("%u", &n);
    
    if (result != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n == 0) {
        fprintf(stderr, "Error: Input must be greater than 0\n");
        return EXIT_FAILURE;
    }
    
    printf("Total set bits from 1 to %u: %u\n", n, countSetBits(n));
    
    return EXIT_SUCCESS;
}