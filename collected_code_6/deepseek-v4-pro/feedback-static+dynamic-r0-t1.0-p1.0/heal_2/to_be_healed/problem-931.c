#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long sum_of_cubes(int n) {
    if (n < 0) {
        return 0;
    }
    
    if (n > 2097151) {
        fprintf(stderr, "Error: n=%d is too large, overflow would occur\n", n);
        return -1;
    }
    
    long long sum = (long long)n * (n + 1) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 301691642253 * 301691642253 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:347,execs:245,op:quick,pos:6)
     */
    return sum * sum;
}

int main(void) {
    int n;
    
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Input must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    long long result = sum_of_cubes(n);
    if (result == -1 && n > 2097151) {
        return EXIT_FAILURE;
    }
    
    printf("Sum of cubes from 1 to %d is %lld\n", n, result);
    
    return EXIT_SUCCESS;
}