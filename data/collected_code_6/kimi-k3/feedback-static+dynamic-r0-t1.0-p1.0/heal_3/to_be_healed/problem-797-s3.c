#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>

int64_t sum_odd_natural(int64_t l, int64_t r) {
    if (l > r || r < 1) {
        return 0;
    }
    
    int64_t start = (l < 1) ? 1 : l;
    int64_t first_odd = (start % 2 == 0) ? start + 1 : start;
    
    if (first_odd > r) {
        return 0;
    }
    
    int64_t last_odd = (r % 2 == 0) ? r - 1 : r;
    int64_t count = (last_odd - first_odd) / 2 + 1;
    
    int64_t sum_first_last;
    if (first_odd <= INT64_MAX - last_odd) {
        sum_first_last = first_odd + last_odd;
    } else {
        int64_t diff = last_odd - first_odd;
        if (diff % 2 == 0) {
            return count * (first_odd + diff / 2);
        } else {
            return (count / 2) * (first_odd + last_odd) + (count % 2) * ((first_odd + last_odd) / 2);
        }
    }
    
    if (count % 2 == 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 5555555555555000 * 22222222222224444 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:2189,execs:675,op:havoc,rep:5)
         * UBSan: signed integer overflow: 55555555555 * 222222222224 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000009,time:21326,execs:6336,op:havoc,rep:7)
         * UBSan: signed integer overflow: 5555555555 * 22222222224 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000003,sig:06,src:000005,time:32196,execs:9485,op:havoc,rep:7)
         */
        return (count / 2) * sum_first_last;
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 49999999999999 * 50000000000001 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000007,time:17385,execs:5227,op:havoc,rep:1)
         */
        return count * (sum_first_last / 2);
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    int64_t l, r;
    char *endptr;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    errno = 0;
    l = strtoll(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer) {
        return 1;
    }
    
    while (*endptr == ' ' || *endptr == '\t') {
        endptr++;
    }
    
    errno = 0;
    r = strtoll(endptr, &endptr, 10);
    if (errno != 0) {
        return 1;
    }
    
    printf("%" PRId64 "\n", sum_odd_natural(l, r));
    
    return 0;
}