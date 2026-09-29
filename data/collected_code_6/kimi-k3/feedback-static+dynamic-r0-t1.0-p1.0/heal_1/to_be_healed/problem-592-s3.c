#include <stdio.h>
#include <stdlib.h>

long long binomial_coefficient(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    if (k > n - k) {
        k = n - k;
    }
    
    long long result = 1;
    for (int i = 0; i < k; i++) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}

long long sum_of_product_of_binomials(int n) {
    long long sum = 0;
    for (int i = 0; i <= n; i++) {
        long long coeff = binomial_coefficient(n, i);
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 6646215757681299270 + 4857445984927644900 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000014,time:20544,execs:10207,op:havoc,rep:15)
         */
        sum += coeff * coeff;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:240,execs:156,op:havoc,rep:5; likely memory-safety defect
  */

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Input must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    long long result = sum_of_product_of_binomials(n);
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}