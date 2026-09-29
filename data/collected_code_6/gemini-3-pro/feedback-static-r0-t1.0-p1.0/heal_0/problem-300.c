#include <stdio.h>
#include <stdlib.h>

unsigned long long compute_nCr(int n, int r) {
    if (r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n / 2) r = n - r;

    unsigned long long res = 1;
    for (int i = 1; i <= r; i++) {
        res = res * (n - i + 1);
        res = res / i;
    }
    return res;
}

unsigned long long count_binary_sequences(int n) {
    if (n < 0) return 0;

    unsigned long long res = 0;
    for (int k = 0; k <= n; k++) {
        unsigned long long nCr = compute_nCr(n, k);
        res += nCr * nCr;
    }
    return res;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    
    if (n < 0 || n > 30) {
        return 1;
    }

    unsigned long long result = count_binary_sequences(n);
    printf("%llu\n", result);

    return 0;
}