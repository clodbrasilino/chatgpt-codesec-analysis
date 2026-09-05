#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long jacobsthal(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    
    long long prev2 = 0;
    long long prev1 = 1;
    long long current = 0;
    
    for (int i = 2; i <= n; i++) {
        if (prev1 > (LLONG_MAX - 2 * prev2)) {
            return -1;
        }
        current = prev1 + 2 * prev2;
        prev2 = prev1;
        prev1 = current;
    }
    
    return current;
}

int main(void) {
    int n;
    
    if (printf("Enter n: ") < 0) {
        return EXIT_FAILURE;
    }
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    long long result = jacobsthal(n);
    
    if (result == -1 && n > 1) {
        fprintf(stderr, "Overflow occurred\n");
        return EXIT_FAILURE;
    }
    
    if (printf("Jacobsthal(%d) = %lld\n", n, result) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}