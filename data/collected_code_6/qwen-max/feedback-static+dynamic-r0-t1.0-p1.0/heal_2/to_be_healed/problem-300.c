#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long countWays(int n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 * 1848304526 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000002,time:865,execs:388,op:havoc,rep:1)
     */
    if (n < 0 || 2 * n + 1 > INT_MAX) {
        return 0;
    }
    long long C[n + 1][n + 1];
    for (int i = 0; i <= n; ++i) {
        C[i][0] = 1;
        C[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            if (C[i - 1][j - 1] > LLONG_MAX - C[i - 1][j]) {
                return 0;
            }
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
    return C[n][n];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000002,time:368,execs:175,op:havoc,rep:11; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    printf("Count of ways: %lld\n", countWays(n));
    return 0;
}