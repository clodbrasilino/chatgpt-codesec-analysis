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
         * ASan: FPE (AFL crash: id:000001,sig:06,src:000001,time:758,execs:920,op:havoc,rep:15)
         * UBSan: division by zero (AFL crash: id:000001,sig:06,src:000001,time:758,execs:920,op:havoc,rep:15)
         * UBSan: signed integer overflow: 3559958832009428378 + 5760134388741632240 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:611,execs:754,op:havoc,rep:5)
         */
        if ((k - 1) > LLONG_MAX / (same + diff) || (k - 1) * (same + diff) < 0 || (k - 1) * (same + diff) > LLONG_MAX) return -1;
        diff = (k - 1) * (same + diff);
        if ((k - 1) > LLONG_MAX / temp || (k - 1) * temp < 0 || (k - 1) * temp > LLONG_MAX) return -1;
        same = (k - 1) * temp;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 5195179504519237332 + 8658632507532062220 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000005,time:54016,execs:48113,op:havoc,rep:8)
     */
    if (same + diff < 0 || same + diff > INT_MAX) return -1;
    return same + diff;
}

int main() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) return -1;
    printf("%d\n", numWays(n, k));
    return 0;
}