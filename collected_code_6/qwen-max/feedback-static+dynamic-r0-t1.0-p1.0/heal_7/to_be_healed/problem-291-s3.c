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
         * UBSan: signed integer overflow: 3559958832009428378 + 5760134388741632240 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:567,execs:586,op:havoc,rep:4)
         */
        if ((k - 1) * (same + diff) > LLONG_MAX) return -1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 3559958832009428378 + 5760134388741632240 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:567,execs:586,op:havoc,rep:4)
         */
        diff = (k - 1) * (same + diff);
        if ((k - 1) * temp > LLONG_MAX) return -1;
        same = (k - 1) * temp;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3843325114289676288 + 5764987671434514432 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000002,time:50145,execs:34122,op:havoc,rep:36)
     * UBSan: signed integer overflow: 7913560244174358148 + 5597305494862156006 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:567,execs:586,op:havoc,rep:4)
     */
    if (same + diff > INT_MAX) return -1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3843325114289676288 + 5764987671434514432 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000002,time:50145,execs:34122,op:havoc,rep:36)
     * UBSan: signed integer overflow: 7913560244174358148 + 5597305494862156006 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:567,execs:586,op:havoc,rep:4)
     */
    return same + diff;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:329,execs:350,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) return -1;
    printf("%d\n", numWays(n, k));
    return 0;
}