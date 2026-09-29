#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long find_largest_k(long long limit, long long x, long long y) {
    if (x <= 0 || y < 0 || y >= x) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775800 + 10 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000005,time:9663,execs:4695,op:havoc,rep:2)
     */
    long long k = limit - (limit % x) + y;
    if (k > limit) {
        k -= x;
    }
    
    if (k < 0) {
        return -1;
    }
    
    return k;
}

int main(void) {
    long long limit;
    long long x;
    long long y;

    if (scanf("%lld %lld %lld", &limit, &x, &y) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    long long result = find_largest_k(limit, x, y);
    if (result == -1) {
        fprintf(stderr, "No valid k found or invalid parameters\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);
    return EXIT_SUCCESS;
}