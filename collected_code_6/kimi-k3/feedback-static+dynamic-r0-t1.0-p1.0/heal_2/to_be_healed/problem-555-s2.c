#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t compute_difference(int64_t n) {
    if (n < 0) {
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:687,execs:297,op:havoc,rep:8)
     * UBSan: signed integer overflow: 333333333333333 * 333333333333334 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:280,execs:133,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:687,execs:297,op:havoc,rep:8)
     */
    int64_t sum = n * (n + 1) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 55555611111 * 55555611111 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000001,time:709,execs:306,op:havoc,rep:8)
     * UBSan: signed integer overflow: -4611686018427387904 * -4611686018427387904 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:687,execs:297,op:havoc,rep:8)
     * UBSan: signed integer overflow: -2792349330601299513 * -2792349330601299513 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:280,execs:133,op:havoc,rep:2)
     */
    int64_t sum_of_cubes = sum * sum;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 6622814520150247601 - -2792349330601299513 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:280,execs:133,op:havoc,rep:2)
     */
    return sum_of_cubes - sum;
}

int main(void) {
    int64_t n;
    if (scanf("%" SCNd64, &n) != 1) {
        return 1;
    }
    printf("%" PRId64 "\n", compute_difference(n));
    return 0;
}