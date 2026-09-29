#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t numWays(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return k;
    int64_t same = 0, diff = k;
    for (int i = 2; i <= n; ++i) {
        int64_t temp = diff;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -1215526009 * 2955006954679884144 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000003,time:6,execs:15,op:(null),pos:0)
         * UBSan: signed integer overflow: 343 * -6683084242404468040 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000003,time:3548,execs:1211,op:havoc,rep:2)
         * UBSan: signed integer overflow: 4481394221449555648 + 7282265609855527928 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000003,time:3548,execs:1211,op:havoc,rep:2)
         */
        diff = (k - 1) * (same + diff);
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4481394221449555648 + 7282265609855527928 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000003,time:3548,execs:1211,op:havoc,rep:2)
         */
        if (diff / (k - 1) != same + temp) break;
        same = (k - 1) * temp;
    }
    return same + diff;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000002,sig:06,src:000003,time:3755,execs:1278,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    printf("%" PRId64 "\n", numWays(n, k));
    return 0;
}