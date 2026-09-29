#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

int numWays(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return k;

    long same = 0, diff = k;
    for (int i = 2; i <= n; ++i) {
        long temp = diff;
        /* Possible weaknesses found:
         * UBSan: division by zero (AFL crash: id:000001,sig:06,src:000002,time:243,execs:319,op:havoc,rep:2)
         * ASan: FPE (AFL crash: id:000001,sig:06,src:000002,time:243,execs:319,op:havoc,rep:2)
         * UBSan: signed integer overflow: -1961633964 * 7696015613513438664 cannot be represented in type 'long' (AFL crash: id:000002,sig:06,src:000002,time:1286,execs:1561,op:havoc,rep:2)
         */
        if (k - 1 > INT_MAX / (same + diff) || (k - 1) * (same + diff) < 0) return -1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -1961633964 * 7696015613513438664 cannot be represented in type 'long' (AFL crash: id:000002,sig:06,src:000002,time:1286,execs:1561,op:havoc,rep:2)
         */
        diff = (k - 1) * (same + diff);
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -1961633964 * 3848007806756719332 cannot be represented in type 'long' (AFL crash: id:000002,sig:06,src:000002,time:1286,execs:1561,op:havoc,rep:2)
         */
        if (k - 1 > INT_MAX / temp || (k - 1) * temp < 0) return -1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -1961633964 * 3848007806756719332 cannot be represented in type 'long' (AFL crash: id:000002,sig:06,src:000002,time:1286,execs:1561,op:havoc,rep:2)
         */
        same = (k - 1) * temp;
    }
    if (same + diff < 0 || same + diff > INT_MAX) return -1;
    return same + diff;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:168,execs:228,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) return -1;
    printf("%d\n", numWays(n, k));
    return 0;
}