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
         * UBSan: signed integer overflow: 249477147 * 124477694249473512 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000003,time:683,execs:315,op:havoc,rep:4)
         * UBSan: signed integer overflow: 5022145529296947162 + 8370242548828245270 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000009,time:6627,execs:2695,op:havoc,rep:3)
         * UBSan: signed integer overflow: 4413 * -5054355995584359184 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000009,time:6627,execs:2695,op:havoc,rep:3)
         */
        int64_t new_diff = (k - 1) * (same + diff);
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 5022145529296947162 + 8370242548828245270 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000009,time:6627,execs:2695,op:havoc,rep:3)
         */
        if (k == 1 || (new_diff / (k - 1) != same + temp) || new_diff > INT64_MAX || new_diff < INT64_MIN) break;
        diff = new_diff;
        int64_t new_same = (k - 1) * temp;
        if (new_same > INT64_MAX || new_same < INT64_MIN) break;
        same = new_same;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 5022145529296947162 + 8370242548828245270 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000009,time:6627,execs:2695,op:havoc,rep:3)
     * UBSan: signed integer overflow: 3662694823375807632 + 6104491372293012720 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000004,time:8650,execs:3497,op:havoc,rep:2)
     */
    int64_t result = same + diff;
    if (result > INT64_MAX || result < INT64_MIN) {
        return 0;
    }
    return result;
}

int main() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) {
        printf("Invalid input\n");
        return 1;
    }
    printf("%" PRId64 "\n", numWays(n, k));
    return 0;
}