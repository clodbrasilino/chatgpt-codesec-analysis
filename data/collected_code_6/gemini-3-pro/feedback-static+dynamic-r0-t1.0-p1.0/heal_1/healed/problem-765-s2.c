#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long int findNthPoliteNumber(long long int n) {
    if (n <= 0) {
        return -1; 
    }
    
    unsigned long long temp = (unsigned long long)n + 1;
    long long int c = 0;
    unsigned long long val = temp;
    
    while (val >>= 1) {
        c++;
    }
    
    if (n > LLONG_MAX - c - 1) {
        return -1;
    }
    
    return n + c + 1;
}

int main(void) {
    long long int n;
    
    if (scanf("%lld", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    if (n <= 0) {
        return EXIT_FAILURE;
    }
    
    long long int result = findNthPoliteNumber(n);
    if (result == -1) {
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}