#include <stdio.h>
#include <stdlib.h>

unsigned long long binomial_coefficient(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    
    if (k == 0 || k == n) {
        return 1;
    }
    
    if (k > n - k) {
        k = n - k;
    }
    
    unsigned long long res = 1;
    
    for (int i = 1; i <= k; ++i) {
        res = res * (n - i + 1) / i;
    }
    
    return res;
}

int main() {
    int n, k;
    
    if (scanf("%d %d", &n, &k) != 2) {
        return 1;
    }
    
    unsigned long long result = binomial_coefficient(n, k);
    printf("%llu\n", result);
    
    return 0;
}