#include <stdio.h>

long long count_cubes(long long n, long long k) {
    if (n < 0 || k <= 0 || k > n) {
        return 0;
    }
    
    long long diff = n - k + 1;
    return diff * diff * diff;
}

int main(void) {
    long long n, k;
    
    printf("Enter size of large cube (n): ");
    scanf("%lld", &n);
    
    printf("Enter size of small cube (k): ");
    scanf("%lld", &k);
    
    long long result = count_cubes(n, k);
    printf("Number of cubes of size %lld in a cube of size %lld: %lld\n", k, n, result);
    
    return 0;
}