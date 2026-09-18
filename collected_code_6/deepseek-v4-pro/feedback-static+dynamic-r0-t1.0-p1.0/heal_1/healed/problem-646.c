#include <stdio.h>
#include <limits.h>

long long safe_multiply(long long a, long long b, int *overflow) {
    if (a > 0 && b > 0 && a > LLONG_MAX / b) {
        *overflow = 1;
        return 0;
    }
    if (a > 0 && b < 0 && b < LLONG_MIN / a) {
        *overflow = 1;
        return 0;
    }
    if (a < 0 && b > 0 && a < LLONG_MIN / b) {
        *overflow = 1;
        return 0;
    }
    if (a < 0 && b < 0 && a < LLONG_MAX / b) {
        *overflow = 1;
        return 0;
    }
    *overflow = 0;
    return a * b;
}

long long count_cubes(long long n, long long k) {
    if (n < 0 || k <= 0 || k > n) {
        return 0;
    }
    
    long long diff = n - k + 1;
    int overflow = 0;
    
    long long square = safe_multiply(diff, diff, &overflow);
    if (overflow) {
        return -1;
    }
    
    long long cube = safe_multiply(square, diff, &overflow);
    if (overflow) {
        return -1;
    }
    
    return cube;
}

int main(void) {
    long long n, k;
    
    printf("Enter size of large cube (n): ");
    if (scanf("%lld", &n) != 1) {
        printf("Invalid input for n.\n");
        return 1;
    }
    
    printf("Enter size of small cube (k): ");
    if (scanf("%lld", &k) != 1) {
        printf("Invalid input for k.\n");
        return 1;
    }
    
    long long result = count_cubes(n, k);
    if (result == -1) {
        printf("Overflow detected: result too large to represent.\n");
    } else {
        printf("Number of cubes of size %lld in a cube of size %lld: %lld\n", k, n, result);
    }
    
    return 0;
}