#include <stdio.h>
#include <math.h>

int count_factorial_digits(int n) {
    if (n < 0) {
        return -1;
    }
    if (n <= 1) {
        return 1;
    }
    double log_sum = 0.0;
    for (int i = 2; i <= n; i++) {
        log_sum += log10((double)i);
    }
    return (int)floor(log_sum) + 1;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    int result = count_factorial_digits(n);
    if (result == -1) {
        return 1;
    }
    printf("%d\n", result);
    return 0;
}