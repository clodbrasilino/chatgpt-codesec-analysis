#include <stdio.h>
#include <limits.h>

long long find_difference(int n) {
    if (n <= 0) {
        return 0;
    }
    
    long long sum = (long long)n * (n + 1) / 2;
    
    if (sum > 0 && sum > LLONG_MAX / sum) {
        return -1;
    }
    
    long long sum_cubes = sum * sum;
    long long diff = sum_cubes - sum;
    
    return diff;
}

int main() {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    
    if (n < 0) {
        return 1;
    }
    
    long long result = find_difference(n);
    
    if (result == -1) {
        return 1;
    }
    
    printf("%lld\n", result);
    
    return 0;
}