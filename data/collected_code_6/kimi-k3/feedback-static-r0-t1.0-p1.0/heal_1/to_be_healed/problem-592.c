#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'ULLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

unsigned long long binomialCoefficient(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    if (k > n - k) {
        k = n - k;
    }
    
    unsigned long long result = 1;
    for (int i = 0; i < k; i++) {
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  'ULLONG_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'ULLONG_MAX'
         */
        if (result > ULLONG_MAX / (n - i)) {
            return 0;
        }
        result = result * (n - i) / (i + 1);
    }
    return result;
}

unsigned long long sumOfProductOfBinomialCoefficients(int n) {
    if (n < 0) {
        return 0;
    }
    
    unsigned long long sum = 0;
    for (int i = 0; i <= n; i++) {
        unsigned long long coeff = binomialCoefficient(n, i);
        if (coeff == 0 && i > 0 && i < n) {
            continue;
        }
        /* Possible weaknesses found:
         *  'ULLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
         *  'ULLONG_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'ULLONG_MAX'
         */
        if (sum > ULLONG_MAX - coeff * coeff) {
            return 0;
        }
        sum += coeff * coeff;
    }
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter a non-negative integer n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = sumOfProductOfBinomialCoefficients(n);
    
    if (result == 0 && n > 0) {
        fprintf(stderr, "Overflow occurred during calculation\n");
        return EXIT_FAILURE;
    }
    
    printf("Sum of products of binomial coefficients C(%d,i) * C(%d,i) for i=0 to %d: %llu\n", n, n, n, result);
    
    return EXIT_SUCCESS;
}