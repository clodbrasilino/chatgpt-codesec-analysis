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
         * UBSan: signed integer overflow: 3559958832009428378 + 5760134388741632240 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:773,execs:882,op:havoc,rep:2)
         */
        if ((k - 1) > LLONG_MAX / (same + diff)) return -1;
        diff = (k - 1) * (same + diff);
        if ((k - 1) > LLONG_MAX / temp) return -1;
        same = (k - 1) * temp;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 - -1 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000009,time:12025,execs:13679,op:havoc,rep:1)
     */
    if (same > LLONG_MAX - diff) return -1;
    return same + diff;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:284,execs:337,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) return -1;
    long long result = numWays(n, k);
    printf("%lld\n", result);
    return 0;
}