#include <stdio.h>
#include <stdlib.h>

long binomial_coefficient(int n, int k) {
    long result = 1;
    if (k > n - k) k = n - k;
    for (int i = 0; i < k; ++i) {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

long sum_of_squares_binomial_coefficients(int n) {
    long sum = 0;
    for (int k = 0; k <= n; ++k) {
        long coefficient = binomial_coefficient(n, k);
        sum += coefficient * coefficient;
    }
    return sum;
}

int main() {
    int n = 6;
    long result = sum_of_squares_binomial_coefficients(n);
    printf("Sum of squares of binomial coefficients of n = %d is %ld\n", n, result);
    return 0;
}