#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t nth_jacobsthal_lucas(int n) {
    if (n == 0) return 2;
    if (n == 1) return 1;

    int64_t a = 2, b = 1;
    for (int i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2 * 4611686018427387905 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:1250,execs:505,op:havoc,rep:4)
         */
        int64_t c = 2 * a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Input must be a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    int64_t result = nth_jacobsthal_lucas(n);
    /* Possible weaknesses found:
     *  %lld in format string (no. 2) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     */
    printf("The %dth Jacobsthal-Lucas number is: %lld\n", n, result);

    return EXIT_SUCCESS;
}