#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int64_t nth_jacobsthal_lucas(int n) {
    if (n == 0) return 2;
    if (n == 1) return 1;

    int64_t a = 2, b = 1;
    for (int i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2 * 4611686018427387905 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:373,execs:162,op:havoc,rep:4)
         */
        int64_t c = 2 * a + b;
        if ((a > 0 && c < 0) || (a < 0 && c > 0)) {
            fprintf(stderr, "Overflow detected.\n");
            exit(EXIT_FAILURE);
        }
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
    printf("The %dth Jacobsthal-Lucas number is: %" PRId64 "\n", n, result);

    return EXIT_SUCCESS;
}