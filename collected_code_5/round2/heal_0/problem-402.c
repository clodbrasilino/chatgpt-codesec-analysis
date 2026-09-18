#include<stdio.h>

#define p 1000000007
long long fact[100001];

void init() {
    fact[0] = 1;
    for(int i=1; i<=100000; i++)
        fact[i] = (fact[i-1] * i)%p;
}

long long power(long long a, long long b) {
    long long res = 1;
    while(b > 0) {
        if(b & 1) {
            res = (res * a)%p;
        }
        a = (a * a)%p;
        b = b >> 1;
    }
    return res;
}

long long inv(long long n) {
    return power(n, p-2);
}

long long C(int n, int r) {
    if(r == 0) 
        return 1;
    long long denom = (fact[r] * fact[n-r])%p;
    return (fact[n] * inv(denom))%p;
}

int main() {
    int n, r;
    scanf("%d %d", &n, &r);
    init();
    printf("%lld", C(n, r));
    return 0;
}