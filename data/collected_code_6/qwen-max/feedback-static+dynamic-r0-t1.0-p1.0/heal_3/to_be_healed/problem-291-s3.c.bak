#include <stdio.h>
#include <stdint.h>

int64_t numWays(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return k;
    int64_t same = 0, diff = k;
    for (int i = 2; i <= n; ++i) {
        int64_t temp = diff;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 3559958832009428378 + 5760134388741632240 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:749,execs:267,op:havoc,rep:2)
         */
        diff = (k - 1) * (same + diff);
        same = (k - 1) * temp;
    }
    return same + diff;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:9,execs:15,op:(null),pos:0; likely memory-safety defect
  */

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     */
    printf("%lld\n", numWays(n, k));
    return 0;
}