#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

long long find_nth_non_multiple(long long n, long long divisor) {
    if (n <= 0 || divisor == 0) {
        return -1;
    }
    
    if (divisor == LLONG_MIN) {
        if (n == 1) {
            return 1;
        }
        if (n == 2) {
            return -1;
        }
        return n - 1;
    }
    
    long long abs_divisor = llabs(divisor);
    
    if (abs_divisor == 1) {
        return -1;
    }
    
    if (n > LLONG_MAX - (n - 1) / (abs_divisor - 1) - 1) {
        return -1;
    }
    
    return n + (n - 1) / (abs_divisor - 1);
}

int main(void) {
    long long n, divisor;
    
    if (scanf("%lld %lld", &n, &divisor) != 2) {
        return EXIT_FAILURE;
    }
    
    long long result = find_nth_non_multiple(n, divisor);
    
    if (result == -1) {
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}