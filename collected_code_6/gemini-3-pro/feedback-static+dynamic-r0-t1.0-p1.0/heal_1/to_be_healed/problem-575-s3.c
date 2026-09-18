#include <stdio.h>
#include <stdlib.h>

long long findNthNotMultiple(long long n, long long k) {
    if (k <= 1 || n < 1) {
        return -1; 
    }
    long long q = n / (k - 1);
    long long r = n % (k - 1);
    
    if (r == 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 * 2 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000004,time:24250,execs:12611,op:havoc,rep:3)
         */
        return q * k - 1;
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1844674407370955161 * 6 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:686,execs:386,op:havoc,rep:3)
         */
        return q * k + r;
    }
}

int main(void) {
    long long n = 0;
    long long k = 0;

    if (scanf("%lld %lld", &n, &k) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    long long result = findNthNotMultiple(n, k);
    if (result == -1) {
        fprintf(stderr, "Invalid parameters.\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}