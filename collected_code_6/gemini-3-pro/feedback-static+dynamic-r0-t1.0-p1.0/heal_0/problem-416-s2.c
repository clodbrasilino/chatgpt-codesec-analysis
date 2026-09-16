#include <stdio.h>

long long max_sum(long long n) {
    if (n == 0) {
        return 0;
    }
    
    long long sum = max_sum(n / 2) + max_sum(n / 3) + max_sum(n / 4);
    
    if (sum > n) {
        return sum;
    } else {
        return n;
    }
}

int main() {
    long long n;
    
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (n < 0) {
        fprintf(stderr, "Number must be non-negative\n");
        return 1;
    }
    
    long long result = max_sum(n);
    printf("%lld\n", result);
    
    return 0;
}