#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long count_cubes(int n, int k) {
    if (n <= 0 || k <= 0 || k > n) {
        return 0;
    }
    
    long long diff = (long long)n - (long long)k + 1;
    
    if (diff > 0 && diff > LLONG_MAX / (diff * diff)) {
        return -1;
    }
    
    return diff * diff * diff;
}

int main(void) {
    int n, k;
    
    if (printf("Enter size of main cube (n): ") < 0) {
        return EXIT_FAILURE;
    }
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }
    
    if (printf("Enter size of sub-cube (k): ") < 0) {
        return EXIT_FAILURE;
    }
    
    if (scanf("%d", &k) != 1) {
        fprintf(stderr, "Invalid input for k\n");
        return EXIT_FAILURE;
    }
    
    long long result = count_cubes(n, k);
    
    if (result == -1) {
        fprintf(stderr, "Result overflow\n");
        return EXIT_FAILURE;
    }
    
    if (printf("Number of cubes: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}