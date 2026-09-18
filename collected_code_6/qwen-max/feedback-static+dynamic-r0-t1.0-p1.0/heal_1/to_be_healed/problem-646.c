#include <stdio.h>
#include <stdlib.h>

long long count_cubes(long n, long k) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -2726062312962348528 * 9223231333615779004 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:323,execs:148,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223231333615779004 * 9223231333615779004 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:323,execs:148,op:havoc,rep:2)
     * UBSan: signed integer overflow: 4938271603950617284 * 2222222222 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:25845,execs:10555,op:havoc,rep:3)
     */
    return (n - k + 1) * (n - k + 1) * (n - k + 1);
}

int main() {
    long n, k;
    scanf("%ld %ld", &n, &k);
    if (n >= k && k > 0) {
        printf("%lld\n", count_cubes(n, k));
    } else {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}