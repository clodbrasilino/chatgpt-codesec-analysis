#include <stdio.h>
#include <stdlib.h>

long long countWays(int n, int k) {
    if (n <= 0 || k <= 0) {
        return 0;
    }
    
    if (n == 1) {
        return k;
    }
    
    if (k == 1) {
        return (n <= 2) ? 1 : 0;
    }
    
    long long same = k;
    long long diff = (long long)k * (k - 1);
    
    for (int i = 3; i <= n; i++) {
        long long newSame = diff;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 3559958832009428378 + 5760134388741632240 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000003,time:15654,execs:5856,op:havoc,rep:2)
         * UBSan: signed integer overflow: 4255197291441457936 * 2062812955 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000003,time:4392,execs:1778,op:havoc,rep:2)
         * UBSan: signed integer overflow: 3662622250513224048 * 3 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:454,execs:213,op:havoc,rep:1)
         * UBSan: signed integer overflow: 8492978622979983808 + 1231137806010546756 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:454,execs:213,op:havoc,rep:1)
         * UBSan: signed integer overflow: 5460024823148808596 + 5875672238617425824 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000003,time:4392,execs:1778,op:havoc,rep:2)
         */
        long long newDiff = (same + diff) * (k - 1);
        same = newSame;
        diff = newDiff;
    }
    
    return same + diff;
}

int main(void) {
    int n, k;
    
    if (scanf("%d %d", &n, &k) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    long long result = countWays(n, k);
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}