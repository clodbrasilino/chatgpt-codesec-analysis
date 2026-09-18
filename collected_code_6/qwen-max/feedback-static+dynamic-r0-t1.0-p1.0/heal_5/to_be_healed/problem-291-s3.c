#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

int64_t numWays(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return k;
    int64_t same = 0, diff = k;
    for (int i = 2; i <= n; ++i) {
        int64_t temp = diff;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -1211913337 * 2937467870373124464 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:8,execs:15,op:(null),pos:0)
         * UBSan: signed integer overflow: 3559958832009428378 + 5760134388741632240 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000002,time:2171,execs:528,op:havoc,rep:15)
         */
        int64_t new_diff = (k - 1) * (same + diff);
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 3559958832009428378 + 5760134388741632240 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000002,time:2171,execs:528,op:havoc,rep:15)
         */
        if (new_diff / (k - 1) != same + temp) break;
        if (new_diff > INT64_MAX || new_diff < INT64_MIN) break;
        diff = new_diff;
        int64_t new_same = (k - 1) * temp;
        if (new_same > INT64_MAX || new_same < INT64_MIN) break;
        same = new_same;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3562937516635623168 + 5768565503124342272 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000003,sig:06,src:000002,time:43372,execs:10450,op:havoc,rep:12)
     * UBSan: signed integer overflow: -6439069776308146982 + -3447490278619531900 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000002,time:2171,execs:528,op:havoc,rep:15)
     */
    return same + diff;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000002,sig:06,src:000002,time:2639,execs:633,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    printf("%" PRId64 "\n", numWays(n, k));
    return 0;
}