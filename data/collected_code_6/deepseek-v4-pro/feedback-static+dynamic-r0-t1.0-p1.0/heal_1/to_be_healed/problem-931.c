#include <stdio.h>
#include <stdlib.h>

long long sum_of_cubes(int n) {
    long long sum = (long long)n * (n + 1) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 617283951049382716 * 617283951049382716 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:10,execs:21,op:havoc,rep:10)
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
    
    printf("Sum of cubes from 1 to %d is %lld\n", n, sum_of_cubes(n));
    
    return EXIT_SUCCESS;
}