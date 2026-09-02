#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    
    long long s_prev2 = 1;
    long long s_prev1 = 1;
    int count = 0;
    long long result = -1;
    
    if (is_prime(s_prev2)) {
        count++;
        if (count == n) return s_prev2;
    }
    
    if (n > 1 && is_prime(s_prev1)) {
        count++;
        if (count == n) return s_prev1;
    }
    
    for (int i = 2; i < 1000000 && count < n; i++) {
        long long s_curr = 2 * s_prev1 + s_prev2;
        if (s_curr < s_prev1) return -1;
        
        if (is_prime(s_curr)) {
            count++;
            if (count == n) {
                result = s_curr;
                break;
            }
        }
        
        s_prev2 = s_prev1;
        s_prev1 = s_curr;
    }
    
    return result;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    long long result = nsw_prime(n);
    if (result == -1) {
        printf("NSW prime not found for n = %d\n", n);
        return EXIT_FAILURE;
    }
    
    printf("The %d-th NSW prime is: %lld\n", n, result);
    return EXIT_SUCCESS;
}