#include <stdio.h>
#include <stdlib.h>

long long countWays(int n, int k) {
    if (n == 0 || k == 0) {
        return 0;
    }
    if (n == 1) {
        return k;
    }

    long long same = k;
    long long diff = (long long)k * (k - 1);
    long long total = same + diff;

    for (int i = 3; i <= n; i++) {
        same = diff;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 3821063618833367449 * 1954754106 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:643,execs:311,op:havoc,rep:5)
         */
        diff = total * (k - 1);
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 3559958832009428378 + 5760134388741632240 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:480,execs:234,op:havoc,rep:1)
         */
        total = same + diff;
    }

    return total;
}

int main(void) {
    int n;
    int k;

    if (scanf("%d %d", &n, &k) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (n < 0 || k < 0) {
        fprintf(stderr, "Input must not be negative\n");
        return 1;
    }

    long long ways = countWays(n, k);
    printf("%lld\n", ways);

    return 0;
}