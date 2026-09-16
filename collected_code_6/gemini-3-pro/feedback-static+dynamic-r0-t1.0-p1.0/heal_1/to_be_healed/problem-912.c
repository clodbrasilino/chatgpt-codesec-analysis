#include <stdio.h>
#include <stdlib.h>

unsigned long long binomial_coefficient(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (k > n - k) {
        k = n - k;
    }
    unsigned long long res = 1;
    for (int i = 0; i < k; ++i) {
        res = res * (n - i);
        res = res / (i + 1);
    }
    return res;
}

unsigned long long lobb_number(int n, int m) {
    if (n < 0 || m < 0 || m > n) {
        return 0;
    }
    unsigned long long term1 = binomial_coefficient(2 * n, n + m);
    /* Possible weaknesses found:
     *  Variable 'term2' is assigned a value that is never used. [unreadVariable]
     *  Value stored to 'term2' during its initialization is never read [deadcode.DeadStores]
     */
    unsigned long long term2 = binomial_coefficient(2 * n, n + m + 1);
    
    unsigned long long result = ((2 * m + 1) * term1) / (n + m + 1);
    return result;
}

int main() {
    int n = 5;
    int m = 2;
    
    unsigned long long result = lobb_number(n, m);
    
    if (result > 0) {
        printf("%llu\n", result);
    }
    
    return 0;
}