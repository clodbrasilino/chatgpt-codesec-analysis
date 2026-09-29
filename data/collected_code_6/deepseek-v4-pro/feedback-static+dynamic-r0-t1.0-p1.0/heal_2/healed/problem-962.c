#include <stdio.h>
#include <limits.h>

long long sum_even_natural_range(long long l, long long r) {
    if (l < 1) {
        l = 1;
    }
    if (r < 1) {
        r = 1;
    }
    if (l > r) {
        return 0;
    }
    if (l % 2 != 0) {
        if (l == LLONG_MAX) {
            return 0;
        }
        l++;
    }
    if (r % 2 != 0) {
        r--;
    }
    if (l > r) {
        return 0;
    }
    if (r - l < 0) {
        return 0;
    }
    long long n = (r - l) / 2 + 1;
    if (n > LLONG_MAX / (l + r)) {
        if (l + r == 0) {
            return 0;
        }
        if (n % 2 == 0) {
            return (n / 2) * (l + r);
        } else {
            return ((l + r) / 2) * n;
        }
    }
    return n * (l + r) / 2;
}

int main(void) {
    long long l, r;
    if (scanf("%lld %lld", &l, &r) != 2) {
        return 1;
    }
    printf("%lld\n", sum_even_natural_range(l, r));
    return 0;
}