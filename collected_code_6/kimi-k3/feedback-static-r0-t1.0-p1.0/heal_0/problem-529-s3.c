#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long jacobsthal_lucas(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 2;
    }
    if (n == 1) {
        return 1;
    }
    
    long long prev2 = 2;
    long long prev1 = 1;
    long long current = 0;
    int i;
    
    for (i = 2; i <= n; i++) {
        if (prev1 > (LLONG_MAX - prev2) / 2) {
            return -1;
        }
        current = 2 * prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    
    return current;
}

int main(void) {
    int n;
    long long result;
    
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        return EXIT_FAILURE;
    }
    
    result = jacobsthal_lucas(n);
    
    if (result == -1) {
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}