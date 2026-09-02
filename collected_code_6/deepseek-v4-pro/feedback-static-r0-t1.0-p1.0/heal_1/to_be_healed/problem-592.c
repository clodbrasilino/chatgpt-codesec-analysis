#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'ULLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

unsigned long long binomial_coefficient(int n, int k) {
    if (k < 0 || k > n || n < 0) {
        return 0;
    }
    if (k > n - k) {
        k = n - k;
    }
    unsigned long long result = 1;
    for (int i = 0; i < k; i++) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}

unsigned long long sum_of_product_of_binomial_coefficients(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    unsigned long long sum = 0;
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= k; j++) {
            unsigned long long term1 = binomial_coefficient(n, i);
            unsigned long long term2 = binomial_coefficient(n, j);
            /* Possible weaknesses found:
             *  use of undeclared identifier 'ULLONG_MAX'
             *  each undeclared identifier is reported only once for each function it appears in
             *  'ULLONG_MAX' undeclared (first use in this function)
             */
            if (term1 > 0 && term2 > ULLONG_MAX / term1) {
                /* Possible weaknesses found:
                 *  use of undeclared identifier 'ULLONG_MAX'
                 */
                return ULLONG_MAX;
            }
            unsigned long long product = term1 * term2;
            /* Possible weaknesses found:
             *  use of undeclared identifier 'ULLONG_MAX'
             */
            if (sum > ULLONG_MAX - product) {
                /* Possible weaknesses found:
                 *  use of undeclared identifier 'ULLONG_MAX'
                 */
                return ULLONG_MAX;
            }
            sum += product;
        }
    }
    return sum;
}

int main(void) {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    if (n < 0 || k < 0 || k > n) {
        fprintf(stderr, "Error: Invalid range\n");
        return EXIT_FAILURE;
    }
    unsigned long long result = sum_of_product_of_binomial_coefficients(n, k);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}