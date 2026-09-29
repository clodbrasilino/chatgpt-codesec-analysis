#include <stdio.h>

int numWays(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return k;
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    int same = 0, diff = k, temp;
    for (int i = 2; i <= n; ++i) {
        temp = diff;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 866988874 + 1402817466 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000002,time:2621,execs:574,op:havoc,rep:4)
         * UBSan: signed integer overflow: 645043540 * 645043541 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000002,time:551,execs:138,op:havoc,rep:1)
         * UBSan: signed integer overflow: 1818065124 + 1818065124 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000002,time:551,execs:138,op:havoc,rep:1)
         */
        diff = (k - 1) * (same + diff);
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 645043540 * 645043541 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000002,time:551,execs:138,op:havoc,rep:1)
         */
        same = (k - 1) * temp;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -1822409774 + -387673870 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000002,time:2621,execs:574,op:havoc,rep:4)
     * UBSan: signed integer overflow: 866988874 + 1402817466 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000002,time:13884,execs:3244,op:havoc,rep:4)
     */
    return same + diff;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:9,execs:15,op:(null),pos:0; likely memory-safety defect
  */

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    printf("%d\n", numWays(n, k));
    return 0;
}