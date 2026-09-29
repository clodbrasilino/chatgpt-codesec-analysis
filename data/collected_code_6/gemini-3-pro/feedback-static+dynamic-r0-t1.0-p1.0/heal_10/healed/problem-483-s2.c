#include <stdio.h>
#include <stdlib.h>

long long get_power(long long n, long long p) {
    long long count = 0;
    while (n > 0) {
        count += n / p;
        n /= p;
    }
    return count;
}

long long findFirstFactorialDivisible(long long x) {
    if (x <= 1) {
        return 1;
    }

    long long result = 1;
    long long tempX = x;

    for (long long p = 2; p * p <= tempX; ++p) {
        if (tempX % p == 0