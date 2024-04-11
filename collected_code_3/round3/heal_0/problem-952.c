#include <stdio.h>

#define MAX 100000
#define MOD 1000000007

long long factorial[MAX];

void precompute() {
    factorial[0] = 1;
    for(int i = 1; i < MAX; i++) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }
}

long long power(long long a, long long b) {
    long long res = 1;
    while(b) {
        if(b & 1) {
            res = (res * a) % MOD;
        }
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

long long modInverse(long long a) {
    return power(a, MOD - 2);
}

long long nCr(long long n, long long r) {
    if(r > n) {
        return 0;
    }
    long long res = factorial[n];
    res = (res * modInverse(factorial[r])) % MOD;
    res = (res * modInverse(factorial[n - r])) % MOD;
    return res;
}

int main() {
    precompute();
    int n, r;
    scanf("%d %d", &n, &r);
    printf("%lld\n", nCr(n, r));
    return 0;
}