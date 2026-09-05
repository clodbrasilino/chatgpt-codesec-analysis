#include <stdio.h>
#include <stdlib.h>

#define MAX_CACHE_SIZE 1000000

long long cache[MAX_CACHE_SIZE];

long long f(long long n) {
    if (n <= 0) {
        return 0;
    }
    if (n < MAX_CACHE_SIZE) {
        if (cache[n] != 0) {
            return cache[n];
        }
    }
    long long sum = f(n / 2) + f(n / 3) + f(n / 4) + f(n / 5);
    long long result = sum > n ? sum : n;
    if (n < MAX_CACHE_SIZE) {
        cache[n] = result;
    }
    return result;
}

int main(void) {
    long long n;
    while (scanf("%lld", &n) == 1) {
        printf("%lld\n", f(n));
    }
    return 0;
}