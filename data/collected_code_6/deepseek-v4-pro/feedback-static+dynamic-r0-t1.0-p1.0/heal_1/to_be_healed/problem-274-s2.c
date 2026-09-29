#include <stdio.h>
#include <stdlib.h>

long long sum_even_binomial_coefficients(int n) {
    if (n < 0) {
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: shift exponent 1228654364 is too large for 64-bit type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:624,execs:328,op:havoc,rep:1)
     */
    long long total = 1LL << n;
    long long sum_even = (total + ((n % 2 == 0) ? 1 : 0)) / 2;
    return sum_even;
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

    long long result = sum_even_binomial_coefficients(n);
    if (result == -1) {
        fprintf(stderr, "Error computing sum\n");
        return EXIT_FAILURE;
    }

    printf("Sum of even-indexed binomial coefficients: %lld\n", result);
    return EXIT_SUCCESS;
}