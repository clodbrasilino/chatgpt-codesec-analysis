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

unsigned long long sum_of_squares_of_binomial_coefficients(int n) {
    if (n < 0) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 * 1303176076 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:52351,execs:1369,op:havoc,rep:10)
     */
    return binomial_coefficient(2 * n, n);
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Input must be non-negative.\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long sum = sum_of_squares_of_binomial_coefficients(n);
    printf("%llu\n", sum);
    
    return EXIT_SUCCESS;
}