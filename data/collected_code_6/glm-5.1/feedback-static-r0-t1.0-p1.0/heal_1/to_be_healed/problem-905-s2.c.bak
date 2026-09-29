#include <stdio.h>
#include <stdlib.h>

unsigned long long binomial_coefficient(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    int i;
    unsigned long long res = 1;
    if (k > n - k) {
        k = n - k;
    }
    for (i = 0; i < k; i++) {
        if (res > (unsigned long long)-1 / (n - i)) {
            return 0;
        }
        res = res * (n - i) / (i + 1);
    }
    return res;
}

unsigned long long sum_of_squares_of_binomial_coefficients(int n) {
    if (n < 0) {
        return 0;
    }
    int k;
    unsigned long long sum = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'coeff' can be reduced. [variableScope]
     */
    unsigned long long coeff;
    for (k = 0; k <= n; k++) {
        coeff = binomial_coefficient(n, k);
        if (coeff == 0 && n > 0 && k > 0 && k < n) {
            return 0;
        }
        if (sum > (unsigned long long)-1 - coeff * coeff) {
            return 0;
        }
        sum += coeff * coeff;
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n;
    if (argc != 2) {
        return 1;
    }
    n = atoi(argv[1]);
    if (n < 0) {
        return 1;
    }
    unsigned long long result = sum_of_squares_of_binomial_coefficients(n);
    printf("%llu\n", result);
    return 0;
}