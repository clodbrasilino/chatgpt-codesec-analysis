#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 2131, got 19601
  *  test case 1 failed: expected 153, got 577
  */

int64_t countWays(int n) {
    if (n == 0 || n == 1) return 1;
    int64_t a = 1, b = 1, c;
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = 2; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4612199207062875081 + 6444863157127625798 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:116,execs:129,op:havoc,rep:3)
         * UBSan: signed integer overflow: 6882627592338442563 * 2 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:116,execs:129,op:havoc,rep:3)
         */
        c = a + b * 2;
        a = b;
        b = c;
    }
    /* Possible weaknesses found:
     *  Uninitialized variable: c
     *  Uninitialized variable: c [uninitvar]
     */
    return c;
}

int main() {
    int n;
    printf("Enter the length of the board (n): ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int64_t result = countWays(n);
    printf("Number of ways to fill 3 x %d board with 2 x 1 dominoes: %ld\n", n, result);
    return EXIT_SUCCESS;
}