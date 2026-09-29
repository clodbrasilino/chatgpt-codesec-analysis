#include <stdio.h>

long long sum_even_natural_numbers(long long l, long long r) {
    if (l > r) {
        return 0;
    }
    if (l <= 0) {
        l = 2;
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
    if (r % 2 != 0) {
        r--;
    }
    if (l > r) {
        return 0;
    }
    long long n = ((r - l) / 2) + 1;
    if (l % 2 == 0 && n > 0 && l > (9223372036854775807LL - l) / n) {
        return -1;
    }
    if (n > 0 && l > 9223372036854775807LL / n) {
        return -1;
    }
    long long temp = n * l;
    if (temp > 9223372036854775807LL - (n - 1)) {
        return -1;
    }
    return temp + n - 1;
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