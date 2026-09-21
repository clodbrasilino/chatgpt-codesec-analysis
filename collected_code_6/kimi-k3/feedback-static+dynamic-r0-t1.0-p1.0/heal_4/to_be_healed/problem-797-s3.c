#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>

static int64_t mul_mod(int64_t a, int64_t b, int64_t m) {
    int64_t result = 0;
    a %= m;
    b %= m;
    while (b > 0) {
        if (b & 1) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -3056617688555751616 + -6664676168257503232 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000009,time:55051,execs:16120,op:havoc,rep:7)
             * UBSan: signed integer overflow: 6057838546272522947 + 5360862697934028800 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000011,time:55250,execs:16181,op:havoc,rep:16)
             * UBSan: signed integer overflow: -7121424779961273568 + -4453999867567538176 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000007,time:45553,execs:13114,op:havoc,rep:3)
             */
            result = (result + a) % m;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4730242844441182208 * 2 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000011,time:55250,execs:16181,op:havoc,rep:16)
         * UBSan: signed integer overflow: 7557202994790400000 * 2 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000009,time:55051,execs:16120,op:havoc,rep:7)
         * UBSan: signed integer overflow: 7111111111111040000 * 2 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000007,time:45553,execs:13114,op:havoc,rep:3)
         */
        a = (a * 2) % m;
        b >>= 1;
    }
    return result;
}

static int64_t safe_sum_odd(int64_t l, int64_t r) {
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
    
    int64_t mod = INT64_MAX;
    
    if (count % 2 == 0) {
        int64_t half_count = count / 2;
        int64_t sum_fl = (first_odd % mod + last_odd % mod) % mod;
        return mul_mod(half_count, sum_fl, mod);
    } else {
        int64_t half_sum = first_odd / 2 + last_odd / 2 + (first_odd % 2 + last_odd % 2) / 2;
        return mul_mod(count, half_sum, mod);
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[512];
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
    if (errno != 0 || endptr == buffer) {
        return 1;
    }
    
    printf("%" PRId64 "\n", safe_sum_odd(l, r));
    
    return 0;
}