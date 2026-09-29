#include <stdio.h>
#include <math.h>

long long count_factorial_digits(int n) {
    if (n < 0) {
        return 0;
    }
    if (n <= 1) {
        return 1;
    }
    double log_sum = 0.0;
    for (int i = 2; i <= n; i++) {
        log_sum += log10(i);
    }
    return (long long)floor(log_sum) + 1;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    long long digits = count_factorial_digits(n);
    printf("%lld\n", digits);
    return 0;
}