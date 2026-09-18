#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long countSetBitsHelper(int n) {
    if (n <= 0) {
        return 0;
    }
    
    int x = 0;
    while ((1LL << x) <= n) {
        x++;
    }
    x--;
    
    long long bits_till_2_to_x = 0;
    if (x > 0) {
        bits_till_2_to_x = (long long)x * (1LL << (x - 1));
    }
    
    long long msb_from_2_to_x_to_n = n - (1LL << x) + 1;
    long long rest = countSetBitsHelper(n - (1LL << x));
    
    return bits_till_2_to_x + msb_from_2_to_x_to_n + rest;
}

long long countSetBits(int n) {
    if (n < 0) {
        return -1;
    }
    return countSetBitsHelper(n);
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Input must be a non-negative integer\n");
        return EXIT_FAILURE;
    }
    
    long long totalBits = countSetBits(n);
    printf("%lld\n", totalBits);
    
    return EXIT_SUCCESS;
}