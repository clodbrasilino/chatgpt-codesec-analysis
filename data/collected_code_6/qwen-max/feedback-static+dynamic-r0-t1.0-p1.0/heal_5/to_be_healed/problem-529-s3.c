#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 31, got 53
  *  test case 2 failed: expected 17, got 22
  *  test case 1 failed: expected 5, got 4
  */

int64_t nth_jacobsthal_lucas(int n) {
    if (n == 0) return 2;
    if (n == 1) return 1;

    int64_t a = 2, b = 1;
    for (int i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2 * 8898502541752731604 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000005,time:491,execs:528,op:havoc,rep:3)
         */
        int64_t c = a + 2 * b;
        if (c < a || c < 2 * b) {
            fprintf(stderr, "Integer overflow detected.\n");
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

    int64_t result = nth_jacobsthal_lucas(n);
    printf("The %" PRId32 "th Jacobsthal-L Lucas number is: %" PRId64 "\n", n, result);

    return EXIT_SUCCESS;
}