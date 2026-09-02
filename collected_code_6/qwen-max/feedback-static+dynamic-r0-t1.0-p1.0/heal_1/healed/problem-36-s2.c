#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

int nth_digit(int a, int b, int n) {
    if (b <= 0 || n < 0) return -1;
    long long result = 0;
    long long remainder = a % (long long)b;
    long long multiplier = 1;
    for (int i = 0; i < n && remainder; ++i) {
        remainder *= 10;
        if (remainder / 10 != (a % (long long)b) * 10) break; // Prevent overflow
        int digit = remainder / b;
        remainder %= b;
        if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10 && multiplier > LLONG_MAX - result * 10)) break; // Prevent overflow
        result += digit * multiplier;
        if (multiplier > LLONG_MAX / 10) break; // Prevent overflow
        multiplier *= 10;
    }
    return remainder == 0 ? -1 : (int)result;
}

int main() {
    int a, b, n;
    scanf("%d %d %d", &a, &b, &n);
    int digit = nth_digit(a, b, n);
    printf("%d\n", digit);
    return 0;
}