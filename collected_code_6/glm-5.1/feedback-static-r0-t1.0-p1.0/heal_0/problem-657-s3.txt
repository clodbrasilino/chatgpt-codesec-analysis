#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int first_factorial_digit(int n) {
    if (n < 0) {
        return -1;
    }
    if (n <= 1) {
        return 1;
    }

    double log_sum = 0.0;
    for (int i = 1; i <= n; i++) {
        log_sum += log10((double)i);
    }

    double fractional_part = log_sum - floor(log_sum);

    int first_digit = (int)floor(pow(10.0, fractional_part));

    if (first_digit == 0) {
        first_digit = 1;
    }

    return first_digit;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    int result = first_factorial_digit(n);
    if (result == -1) {
        return 1;
    }

    printf("%d\n", result);
    return 0;
}