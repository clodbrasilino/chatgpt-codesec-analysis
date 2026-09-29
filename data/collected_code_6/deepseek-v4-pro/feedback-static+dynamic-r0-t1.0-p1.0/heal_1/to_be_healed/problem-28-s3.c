#include <stdio.h>
#include <stdlib.h>

long long binomial_coefficient(int n, int k) {
    if (k < 0 || k > n || n < 0) {
        return 0;
    }
    
    if (k > n - k) {
        k = n - k;
    }
    
    long long result = 1;
    for (int i = 0; i < k; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 11793683800920115 * 153581793 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:1151,execs:633,op:havoc,rep:2)
         */
        result = result * (n - i) / (i + 1);
    }
    
    return result;
}

int main(void) {
    int n, k;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter k: ");
    if (scanf("%d", &k) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("C(%d, %d) = %lld\n", n, k, binomial_coefficient(n, k));
    
    return EXIT_SUCCESS;
}