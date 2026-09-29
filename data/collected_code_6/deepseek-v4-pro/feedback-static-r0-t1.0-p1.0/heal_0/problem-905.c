#include <stdio.h>
#include <stdlib.h>

unsigned long long binom(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;
    unsigned long long res = 1;
    for (int i = 0; i < k; i++) {
        if (res > (unsigned long long)-1 / (n - i)) return 0;
        res = res * (n - i) / (i + 1);
    }
    return res;
}

unsigned long long sum_squares_binom(int n) {
    unsigned long long sum = 0;
    for (int k = 0; k <= n; k++) {
        unsigned long long b = binom(n, k);
        if (b != 0 && sum > (unsigned long long)-1 - b * b) return 0;
        sum += b * b;
    }
    return sum;
}

int main(void) {
    int n;
    char buffer[64];
    char *endptr;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    n = (int)strtol(buffer, &endptr, 10);
    if (endptr == buffer || *endptr != '\n' && *endptr != '\0' || n < 0) {
        return 1;
    }
    
    unsigned long long result = sum_squares_binom(n);
    printf("%llu\n", result);
    
    return 0;
}