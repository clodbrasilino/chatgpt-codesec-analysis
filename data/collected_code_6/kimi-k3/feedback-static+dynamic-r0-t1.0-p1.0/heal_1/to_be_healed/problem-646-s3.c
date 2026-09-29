#include <stdio.h>

long long count_cubes(long long n, long long k) {
    if (n <= 0 || k <= 0 || k > n) {
        return 0;
    }
    long long diff = n - k + 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 8888888888888882 * 8888888888888882 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:447,execs:210,op:havoc,rep:1)
     * UBSan: signed integer overflow: 597530793580249 * 24444443 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000005,time:3200,execs:1393,op:havoc,rep:3)
     * UBSan: signed integer overflow: 656138868793770436 * 8888888888888882 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:447,execs:210,op:havoc,rep:1)
     */
    return diff * diff * diff;
}

int main(void) {
    long long n, k;
    
    printf("Enter cube size n: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("Enter sub-cube size k: ");
    if (scanf("%lld", &k) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    long long result = count_cubes(n, k);
    printf("Number of cubes of size %lld in cube of size %lld: %lld\n", k, n, result);
    
    return 0;
}