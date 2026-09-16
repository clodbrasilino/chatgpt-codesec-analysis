#include <stdio.h>
#include <stdlib.h>

unsigned long long binomial_coefficient(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    if (k > n / 2) {
        k = n - k;
    }
    
    unsigned long long res = 1;
    for (int i = 1; i <= k; ++i) {
        res = res * (n - i + 1);
        res = res / i;
    }
    
    return res;
}

unsigned long long lobb_number(int n, int m) {
    if (n < 0 || m < 0 || n < m) {
        return 0;
    }
    
    unsigned long long bin_coeff = binomial_coefficient(2 * n, n + m);
    unsigned long long lobb = ((2ULL * m + 1ULL) * bin_coeff) / (n + m + 1ULL);
    
    return lobb;
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'n=5', assigned value is 5
     */
    int n = 5;
    /* Possible weaknesses found:
     *  Assignment 'm=3', assigned value is 3
     */
    int m = 3;
    
    /* Possible weaknesses found:
     *  Condition 'm<0' is always false
     *  Condition 'n<m' is always false
     *  Condition 'n<m' is always false [knownConditionTrueFalse]
     *  Condition 'm<0' is always false [knownConditionTrueFalse]
     */
    if (n < m || m < 0) {
        fprintf(stderr, "Invalid input bounds. Ensure n >= m >= 0.\n");
        return 1;
    }
    
    unsigned long long result = lobb_number(n, m);
    printf("%llu\n", result);
    
    return 0;
}