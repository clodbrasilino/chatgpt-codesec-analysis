#include <stdio.h>
#include <stdlib.h>

long long countWays(int n, int k) {
    if (n <= 0 || k <= 0) {
        return 0;
    }
    if (n == 1) {
        return k;
    }
    
    long long same = k;
    long long diff = (long long)k * (k - 1);
    long long total = same + diff;
    
    for (int i = 3; i <= n; i++) {
        long long newSame = diff;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1509591546176244496 * 1228654363 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000003,time:3800,execs:1470,op:havoc,rep:1)
         * UBSan: signed integer overflow: 3662622250513224048 * 3 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:281,execs:138,op:havoc,rep:2)
         */
        long long newDiff = total * (k - 1);
        same = newSame;
        diff = newDiff;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 8492978622979983808 + 1231137806010546756 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:281,execs:138,op:havoc,rep:2)
         */
        total = same + diff;
    }
    
    return total;
}

int main(void) {
    int n, k;
    
    if (scanf("%d %d", &n, &k) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0 || k < 0) {
        fprintf(stderr, "Invalid input: n and k must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    long long result = countWays(n, k);
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}