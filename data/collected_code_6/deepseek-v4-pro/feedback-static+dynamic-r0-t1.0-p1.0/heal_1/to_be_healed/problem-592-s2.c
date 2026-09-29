#include <stdio.h>
#include <stdlib.h>

long long binomial_coefficient(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    if (k > n - k) k = n - k;
    
    long long result = 1;
    for (int i = 0; i < k; i++) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}

long long sum_of_product_binomial(int n) {
    if (n < 0) return 0;
    
    long long sum = 0;
    for (int i = 0; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 6646215757681299270 + 4857445984927644900 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:2112,execs:963,op:havoc,rep:2)
         * UBSan: signed integer overflow: 6692148561782392259 + 3478530500497858576 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:218,execs:125,op:havoc,rep:1)
         * UBSan: signed integer overflow: 7669339132 * 7669339132 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:218,execs:125,op:havoc,rep:1)
         */
        sum += binomial_coefficient(n, i) * binomial_coefficient(n, i);
    }
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    long long result = sum_of_product_binomial(n);
    printf("Sum of product of binomial coefficients: %lld\n", result);
    
    return EXIT_SUCCESS;
}