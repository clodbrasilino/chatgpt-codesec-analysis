#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long int find_star_number(int n) {
    if (n <= 0) {
        return -1;
    }
    
    if (n > 1 && (LLONG_MAX - 1) / 6 / n < (n - 1)) {
        return -1;
    }
    
    return 6LL * n * (n - 1) + 1;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    long long int result = find_star_number(n);
    
    if (result == -1) {
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}