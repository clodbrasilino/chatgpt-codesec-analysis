#include <stdio.h>

int numWays(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return k;

    int same = 0, diff = k;

    for (int i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 866988874 + 1402817466 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000002,time:6409,execs:1478,op:havoc,rep:1)
         * UBSan: signed integer overflow: -846706916 + -1409793036 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000004,time:5171,execs:1192,op:havoc,rep:2)
         */
        int sum = same + diff;
        same = diff;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -846706917 * -846706916 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000004,time:5171,execs:1192,op:havoc,rep:2)
         */
        diff = (k - 1) * sum;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1174014140 + 1482357748 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000004,time:5171,execs:1192,op:havoc,rep:2)
     * UBSan: signed integer overflow: 58697100 + 2111508000 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000008,time:34899,execs:5722,op:havoc,rep:1)
     */
    return same + diff;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:7,execs:15,op:(null),pos:0; likely memory-safety defect
  */

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    printf("%d\n", numWays(n, k));
    return 0;
}