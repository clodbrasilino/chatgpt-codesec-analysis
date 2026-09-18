#include <stdio.h>

long long sum_odd_natural_numbers(int l, int r) {
    if (l <= 0) {
        l = 1;
    }
    if (r < l) {
        return 0;
    }
    if (l % 2 == 0) {
        l++;
    }
    if (r % 2 == 0) {
        r--;
    }
    if (l > r) {
        return 0;
    }
    long long a = l;
    long long b = r;
    long long n = ((b - a) / 2) + 1;
    if (n % 2 == 0) {
        return (n / 2) * (a + b);
    } else {
        return n * ((a + b) / 2);
    }
}

int main() {
    int l, r;
    if (scanf("%d %d", &l, &r) != 2) {
        return 1;
    }
    long long result = sum_odd_natural_numbers(l, r);
    printf("%lld\n", result);
    return 0;
}