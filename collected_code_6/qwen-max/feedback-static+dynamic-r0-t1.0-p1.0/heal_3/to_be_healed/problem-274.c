#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  'LLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

long long binomial_coefficient(int n, int k) {
    long long res = 1;
    if (k > n - k)
        k = n - k;
    for (int i = 0; i < k; ++i) {
        /* Possible weaknesses found:
         *  'LLONG_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'LLONG_MAX'
         *  each undeclared identifier is reported only once for each function it appears in
         */
        if (res > LLONG_MAX / (n - i))
            return -1;
        res = res * (n - i) / (i + 1);
    }
    return res;
}

long long sum_even_index_binomial_coefficients(int n) {
    long long sum = 0;
    for (int i = 0; i <= n; i += 2) {
        long long coeff = binomial_coefficient(n, i);
        if (coeff == -1)
            return -1;
        sum += coeff;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }
    long long result = sum_even_index_binomial_coefficients(n);
    if (result == -1) {
        fprintf(stderr, "Overflow occurred. Try a smaller value of n.\n");
        return EXIT_FAILURE;
    }
    printf("Sum of even index binomial coefficients: %lld\n", result);
    return EXIT_SUCCESS;
}