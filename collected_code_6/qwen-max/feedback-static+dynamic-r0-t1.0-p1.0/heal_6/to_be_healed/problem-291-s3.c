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
         * UBSan: signed integer overflow: 4025457557704230864 + 6709095929507051440 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:2391,execs:2430,op:havoc,rep:5)
         */
        if (k - 1 > LLONG_MAX / (same + diff) || (k - 1) * (same + diff) < 0 || (k - 1) * (same + diff) > LLONG_MAX) return -1;
        diff = (k - 1) * (same + diff);
        if (k - 1 > LLONG_MAX / temp || (k - 1) * temp < 0 || (k - 1) * temp > LLONG_MAX) return -1;
        same = (k - 1) * temp;
    }
    if (same + diff < 0 || same + diff > INT_MAX) return -1;
    return same + diff;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000006,time:2758,execs:2785,op:havoc,rep:6; likely memory-safety defect
  */

int main() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) return -1;
    printf("%d\n", numWays(n, k));
    return 0;
}