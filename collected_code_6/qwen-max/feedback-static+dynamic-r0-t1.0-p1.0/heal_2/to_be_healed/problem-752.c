#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 5, got 12
  *  test case 1 failed: expected 1, got 2
  *  test case 0 failed: expected 11, got 29
  */

long long jacobsthal(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    long long a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4866752642924153522 + 5052016396815640554 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:375,execs:378,op:havoc,rep:6)
         * UBSan: signed integer overflow: 2 * 4866752642924153522 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:375,execs:378,op:havoc,rep:6)
         */
        long long c = a + 2 * b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }
    printf("The %dth Jacobsthal number is: %lld\n", n, jacobsthal(n));
    return EXIT_SUCCESS;
}