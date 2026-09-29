#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

static bool is_prime(long long n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

static long long nsw_prime(int n) {
    if (n <= 0) return -1;
    
    long long prev2 = 1;
    long long prev1 = 1;
    int count = 0;
    
    while (count < n) {
        if (prev1 > (LLONG_MAX - prev2) / 2) return -1;
        long long current = 2 * prev1 + prev2;
        
        if (is_prime(current)) {
            count++;
            if (count == n) return current;
        }
        
        prev2 = prev1;
        prev1 = current;
    }
    
    return -1;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    long long result = nsw_prime(n);
    if (result < 0) {
        fprintf(stderr, "Unable to compute\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}