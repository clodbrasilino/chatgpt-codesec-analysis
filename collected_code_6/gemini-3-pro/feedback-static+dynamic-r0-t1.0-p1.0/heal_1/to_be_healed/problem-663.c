#include <stdio.h>
#include <stdlib.h>

long long findLargestK(long long n, long long x, long long y) {
    if (x <= 0) {
        return -1;
    }
    
    long long remainder = n % x;
    long long k;
    
    if (remainder >= y) {
        k = n - remainder + y;
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775790 + 516 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:997,execs:479,op:havoc,rep:4)
         */
        k = n - remainder - x + y;
    }
    
    if (k > n || k < 0) {
        return -1;
    }
    
    return k;
}

int main() {
    long long n, x, y;
    
    if (scanf("%lld %lld %lld", &n, &x, &y) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    long long result = findLargestK(n, x, y);
    
    if (result == -1) {
        printf("No such k exists\n");
    } else {
        printf("%lld\n", result);
    }
    
    return EXIT_SUCCESS;
}