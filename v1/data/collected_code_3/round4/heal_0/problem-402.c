#include<stdio.h>

#define p 1000000007

long long factorial(int n) {
    long long fact = 1;
    for(int i = 1; i <= n; i++) {
        fact = (fact * i) % p;
    }
    return fact;
}

long long power(long long x, int y) {
    long long res = 1;
    while(y > 0) {
        if(y & 1) {
            res = (res * x) % p;
        }
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

long long modInverse(long long n) {
    return power(n, p - 2);
}

long long nCr(int n, int r) {
    if(r == 0) {
        return 1;
    }
    long long fact_n = factorial(n);
    long long fact_r = factorial(r);
    long long fact_nr = factorial(n - r);
    return (fact_n * modInverse(fact_r) % p * modInverse(fact_nr) % p) % p;
}

int main() {
    int n, r;
    printf("Enter the values of n and r: ");
    scanf("%d %d", &n, &r);
    printf("The value of nCr mod p is: %lld", nCr(n, r));
    return 0;
}