#include <stdio.h>
#include <limits.h>

int numWays(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return k;
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    long same = 0, diff = k, temp;
    for (int i = 2; i <= n; ++i) {
        temp = diff;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -1275550393 * 3254057607613808112 cannot be represented in type 'long'
         * UBSan: signed integer overflow: -844706917 * 1427059549565875944 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000003,time:763,execs:780,op:havoc,rep:6)
         */
        if ((k - 1) > INT_MAX / (same + diff) || (k - 1) * (same + diff) < 0) return -1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -1275550393 * 3254057607613808112 cannot be represented in type 'long'
         * UBSan: signed integer overflow: -844706917 * 1427059549565875944 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000003,time:763,execs:780,op:havoc,rep:6)
         */
        diff = (k - 1) * (same + diff);
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -1275550393 * 1627028803806904056 cannot be represented in type 'long'
         * UBSan: signed integer overflow: -844706917 * 713529774782937972 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000003,time:763,execs:780,op:havoc,rep:6)
         */
        if ((k - 1) > INT_MAX / temp || (k - 1) * temp < 0) return -1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -1275550393 * 1627028803806904056 cannot be represented in type 'long'
         */
        same = (k - 1) * temp;
    }
    if (same + diff < 0 || same + diff > INT_MAX) return -1;
    return same + diff;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:485,execs:499,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    printf("%d\n", numWays(n, k));
    return 0;
}