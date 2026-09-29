#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 2131, got 19601
  *  test case 1 failed: expected 153, got 577
  */

int64_t countWays(int n) {
    if (n == 0 || n == 1) return 1;
    int64_t a = 1, b = 1;
    for (int i = 2; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 6882627592338442563 * 2 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:161,execs:180,op:havoc,rep:5)
         */
        int64_t c = a + b * 2;
        if (c < 0 || c > INT64_MAX) return -1;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n;
    printf("Enter the length of the board (n): ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int64_t result = countWays(n);
    if (result == -1) {
        fprintf(stderr, "Overflow detected\n");
        return EXIT_FAILURE;
    }
    printf("Number of ways to fill 3 x %d board with 2 x 1 dominoes: %lld\n", n, (long long)result);
    return EXIT_SUCCESS;
}