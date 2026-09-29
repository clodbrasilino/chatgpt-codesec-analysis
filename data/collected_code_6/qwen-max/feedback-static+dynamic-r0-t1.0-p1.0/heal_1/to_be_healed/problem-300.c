#include <stdio.h>
#include <stdlib.h>

long long countWays(int n) {
    /* Possible weaknesses found:
     * UBSan: variable length array bound evaluates to non-positive value -1 (AFL crash: id:000003,sig:06,src:000008,time:8337,execs:3493,op:havoc,rep:4)
     * UBSan: signed integer overflow: 2 * -2052810070 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:1022,execs:465,op:havoc,rep:9)
     */
    long long C[2 * n + 1][2 * n + 1];
    for (int i = 0; i <= 2 * n; ++i) {
        C[i][0] = 1;
        C[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 4472995859186094240 + 5516694892996182896 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000000,time:1832,execs:793,op:havoc,rep:16)
             */
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
    return C[2 * n][n];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:11,src:000000,time:1474,execs:649,op:havoc,rep:15; likely memory-safety defect
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