#include <stdio.h>

int numWays(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return k;
    int same = 0, diff = k;
    for (int i = 2; i <= n; ++i) {
        int temp = diff;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 866988874 + 1402817466 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:1319,execs:432,op:havoc,rep:2)
         * UBSan: signed integer overflow: -1212685427 * -1212685426 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000001,time:1332,execs:437,op:havoc,rep:2)
         */
        diff = (k - 1) * (same + diff);
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -1212685427 * -1212685426 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000001,time:1332,execs:437,op:havoc,rep:2)
         */
        same = (k - 1) * temp;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1804681014 + 1804681014 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000001,time:1332,execs:437,op:havoc,rep:2)
     * UBSan: signed integer overflow: 1955541062 + 1955541062 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000001,time:9043,execs:2744,op:havoc,rep:4)
     */
    return same + diff;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:6,execs:15,op:(null),pos:0; likely memory-safety defect
  */

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    printf("%d\n", numWays(n, k));
    return 0;
}