#include <stdio.h>
#include <stdlib.h>

long long countWays(int n, int k) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return k;
    }
    if (k == 0) {
        return 0;
    }

    long long same = k;
    long long diff = (long long)k * (k - 1);
    long long total = same + diff;

    for (int i = 3; i <= n; i++) {
        same = diff;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 15095915363470096 * 122865435 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000003,time:9056,execs:4066,op:havoc,rep:1)
         * UBSan: signed integer overflow: 3662622250513224048 * 3 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:513,execs:234,op:havoc,rep:2)
         */
        diff = total * (k - 1);
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 3559958832009428378 + 5760134388741632240 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000015,time:41691,execs:15303,op:havoc,rep:1)
         * UBSan: signed integer overflow: 8492978622979983808 + 1231137806010546756 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:513,execs:234,op:havoc,rep:2)
         */
        total = same + diff;
    }

    return total;
}

int main(void) {
    int n = 0;
    int k = 0;

    if (scanf("%d %d", &n, &k) != 2) {
        return 1;
    }

    if (n < 0 || k < 0) {
        return 1;
    }

    long long result = countWays(n, k);
    printf("%lld\n", result);

    return 0;
}