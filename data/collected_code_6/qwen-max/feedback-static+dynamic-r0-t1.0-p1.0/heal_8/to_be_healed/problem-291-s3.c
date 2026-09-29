#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

int numWays(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return k;

    long long same = 0, diff = k;
    for (int i = 2; i <= n; ++i) {
        long long temp = diff;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 3559958832009428378 + 5760134388741632240 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:646,execs:729,op:havoc,rep:1)
         * ASan: FPE (AFL crash: id:000001,sig:06,src:000006,time:1163,execs:1335,op:havoc,rep:3)
         * UBSan: division by zero (AFL crash: id:000001,sig:06,src:000006,time:1163,execs:1335,op:havoc,rep:3)
         */
        if ((k - 1) > LLONG_MAX / (same + diff)) return -1;
        diff = (k - 1) * (same + diff);
        if ((k - 1) > LLONG_MAX / temp) return -1;
        same = (k - 1) * temp;
    }
    if (same + diff > LLONG_MAX) return -1;
    return same + diff;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000002,sig:06,src:000005,time:2263,execs:2319,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) return -1;
    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed int'. [invalidPrintfArgType_sint]
     */
    printf("%lld\n", numWays(n, k));
    return 0;
}