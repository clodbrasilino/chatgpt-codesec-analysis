#include <stdio.h>

long long count_cubes(long long n, long long k) {
    if (n < 0 || k <= 0 || k > n) {
        return 0;
    }
    
    long long diff = n - k + 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 4938271603950617284 * 2222222222 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:31081,execs:14250,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223231333615779004 * 9223231333615779004 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:406,execs:192,op:havoc,rep:4)
     * UBSan: signed integer overflow: -2726062312962348528 * 9223231333615779004 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:406,execs:192,op:havoc,rep:4)
     */
    return diff * diff * diff;
}

int main(void) {
    long long n, k;
    
    printf("Enter size of large cube (n): ");
    scanf("%lld", &n);
    
    printf("Enter size of small cube (k): ");
    scanf("%lld", &k);
    
    long long result = count_cubes(n, k);
    printf("Number of cubes of size %lld in a cube of size %lld: %lld\n", k, n, result);
    
    return 0;
}