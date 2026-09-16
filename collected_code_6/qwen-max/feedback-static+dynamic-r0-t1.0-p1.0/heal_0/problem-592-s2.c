#include <stdio.h>
#include <stdlib.h>

long binomial_coefficient(long n, long k) {
    long result = 1;
    if (k > n - k) {
        k = n - k;
    }
    for (long i = 0; i < k; ++i) {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

long sum_of_product_of_binomial_coefficients(long n) {
    long sum = 0;
    for (long r = 0; r <= n; ++r) {
        sum += binomial_coefficient(n, r) * binomial_coefficient(n, r);
    }
    return sum;
}

int main() {
    long n = 5;
    long result = sum_of_product_of_binomial_coefficients(n);
    printf("Sum of product of binomial coefficients for n = %ld is: %ld\n", n, result);
    return 0;
}