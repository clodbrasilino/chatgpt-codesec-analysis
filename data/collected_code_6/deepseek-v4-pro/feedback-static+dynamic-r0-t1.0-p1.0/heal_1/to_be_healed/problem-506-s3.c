#include <stdio.h>
#include <stdlib.h>

long long permutation_coefficient(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return -1;
    }

    long long result = 1;
    for (int i = 0; i < k; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1684971720604972800 * 101 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:347,execs:191,op:havoc,rep:1)
         */
        result *= (n - i);
    }
    return result;
}

int main(void) {
    int n, k;
    printf("Enter n and k: ");
    if (scanf("%d %d", &n, &k) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    long long result = permutation_coefficient(n, k);
    if (result < 0) {
        fprintf(stderr, "Invalid values: require 0 <= k <= n\n");
        return EXIT_FAILURE;
    }

    printf("P(%d, %d) = %lld\n", n, k, result);
    return EXIT_SUCCESS;
}