#include <stdio.h>

#define p 1000000007

long long factorial(int n) {
    long long fact = 1;
    for(int i = 2; i <= n; i++)
        fact = (fact * i) % p;
    return fact;
}

long long power(long long x, int y) {
    long long res = 1;
    while(y > 0) {
        if(y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

long long modInverse(long long n) {
    return power(n, p - 2);
}

long long nCrModP(int n, int r) {
    if(r > n)
        return 0;
    long long fact_n = factorial(n);
    long long fact_r = factorial(r);
    long long fact_nr = factorial(n - r);
    return (fact_n * modInverse(fact_r) % p * modInverse(fact_nr) % p) % p;
}

int main() {
    int n = 10, r = 2;
    printf("Value of nCr mod p is %lld", nCrModP(n, r));
    return 0;
}