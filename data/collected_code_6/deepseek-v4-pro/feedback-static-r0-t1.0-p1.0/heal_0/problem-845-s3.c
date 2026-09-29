#include <stdio.h>
#include <math.h>

int count_digits_in_factorial(int n) {
    if (n < 0) {
        return -1;
    }
    if (n <= 1) {
        return 1;
    }
    double log_sum = 0.0;
    for (int i = 2; i <= n; i++) {
        log_sum += log10(i);
    }
    return (int)floor(log_sum) + 1;
}

int main(void) {
    int n;
    printf("Enter a number: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    int digits = count_digits_in_factorial(n);
    if (digits == -1) {
        fprintf(stderr, "Factorial is not defined for negative numbers\n");
        return 1;
    }
    printf("Number of digits in %d! is %d\n", n, digits);
    return 0;
}