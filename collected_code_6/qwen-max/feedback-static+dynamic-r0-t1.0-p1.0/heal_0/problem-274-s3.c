#include <stdio.h>
#include <stdlib.h>

int binomial_coefficient(int n, int k) {
    if (k > n - k) k = n - k;
    int res = 1;
    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

int sum_even_index_binomial_coefficients(int n) {
    int sum = 0;
    for (int i = 0; i <= n; i += 2) {
        sum += binomial_coefficient(n, i);
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a value for n: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int result = sum_even_index_binomial_coefficients(n);
    printf("Sum of even index binomial coefficients: %d\n", result);
    return EXIT_SUCCESS;
}