#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long count_cubes(int n, int k) {
    /* Possible weaknesses found:
     *  Assuming that condition 'k>n' is not redundant
     */
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    
    /* Possible weaknesses found:
     *  Assignment 'diff=(long long)n-k+1', assigned value is greater than 0
     */
    long long diff = (long long)n - k + 1;
    
    /* Possible weaknesses found:
     *  Condition 'diff>0' is always true
     *  Condition 'diff>0' is always true [knownConditionTrueFalse]
     */
    if (diff > 0 && diff > LLONG_MAX / diff) {
        return -1;
    }
    long long square = diff * diff;
    
    if (square > 0 && diff > LLONG_MAX / square) {
        return -1;
    }
    
    return square * diff;
}

int main(void) {
    int n, k;
    
    printf("Enter cube size n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter sub-cube size k: ");
    if (scanf("%d", &k) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0 || k < 0) {
        fprintf(stderr, "Sizes must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    long long result = count_cubes(n, k);
    if (result == -1 && k <= n) {
        fprintf(stderr, "Result too large to compute\n");
        return EXIT_FAILURE;
    }
    
    printf("Number of %d-sized cubes in %d-sized cube: %lld\n", 
           k, n, result);
    
    return EXIT_SUCCESS;
}