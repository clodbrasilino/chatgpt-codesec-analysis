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
    
    if (sum > LLONG_MAX / sum) {
        fprintf(stderr, "Error: multiplication overflow for n=%d\n", n);
        return -1;
    }
    
    return sum * sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:3209,execs:2128,op:havoc,rep:14; likely memory-safety defect
  */

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