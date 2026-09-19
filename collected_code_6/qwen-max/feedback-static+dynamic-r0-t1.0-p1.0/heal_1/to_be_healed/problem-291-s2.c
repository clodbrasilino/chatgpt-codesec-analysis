#include <stdio.h>

int numWays(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return k;
    
    /* Possible weaknesses found:
     *  The scope of the variable 'sum' can be reduced. [variableScope]
     */
    int same = 0, diff = k, sum;
    
    for (int i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 866988874 + 1402817466 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000001,time:6337,execs:1483,op:havoc,rep:4)
         */
        sum = same + diff;
        same = diff;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2065812955 * 2065812956 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:627,execs:175,op:havoc,rep:4)
         */
        diff = (k - 1) * sum;
    }
    
    return same + diff;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:7,execs:15,op:(null),pos:0; likely memory-safety defect
  */

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    printf("%d\n", numWays(n, k));
    return 0;
}