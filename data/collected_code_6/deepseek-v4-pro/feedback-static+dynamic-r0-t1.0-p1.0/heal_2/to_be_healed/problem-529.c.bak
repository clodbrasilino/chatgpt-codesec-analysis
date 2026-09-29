#include <stdio.h>
#include <stdlib.h>

long long jacobsthal_lucas(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: negative input not allowed\n");
        exit(EXIT_FAILURE);
    }
    if (n == 0) return 2;
    if (n == 1) return 1;
    
    long long a = 2;
    long long b = 1;
    long long result = 0;
    
    for (int i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2 * 4611686018427387905 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:264,execs:144,op:havoc,rep:8)
         */
        result = b + 2 * a;
        a = b;
        b = result;
    }
    
    return result;
}

int main(void) {
    int n;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Jacobsthal-Lucas(%d) = %lld\n", n, jacobsthal_lucas(n));
    
    return EXIT_SUCCESS;
}