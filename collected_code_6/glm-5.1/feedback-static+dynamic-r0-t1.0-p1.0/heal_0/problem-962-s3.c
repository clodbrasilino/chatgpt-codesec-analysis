#include <stdio.h>

long long sum_even_natural_numbers(long long l, long long r) {
    if (l > r) {
        return 0;
    }
    if (l <= 0) {
        l = 1;
    }
    if (r <= 0) {
        return 0;
    }
    if (l % 2 != 0) {
        l++;
    }
    if (l > r) {
        return 0;
    }
    long long n = ((r - l) / 2) + 1;
    return n * (l + r - ((r % 2 != 0) ? 1 : 0)) / 2;
}

int main() {
    long long l, r;
    if (scanf("%lld %lld", &l, &r) != 2) {
        return 1;
    }
    long long result = sum_even_natural_numbers(l, r);
    printf("%lld\n", result);
    return 0;
}