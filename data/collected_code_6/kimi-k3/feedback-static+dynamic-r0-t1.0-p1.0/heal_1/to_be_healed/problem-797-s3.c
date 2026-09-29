#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

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
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 111111111110 * 222222222224 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:8526,execs:3574,op:havoc,rep:3)
     * UBSan: signed integer overflow: 4611686018427387901 * -9223372036854775802 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000005,time:3718,execs:1538,op:havoc,rep:3)
     * UBSan: signed integer overflow: 7 + 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000005,time:3718,execs:1538,op:havoc,rep:3)
     */
    return count * (first_odd + last_odd) / 2;
}

int main(void) {
    int64_t l, r;
    
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64 " %" SCNd64, &l, &r) != 2) {
        return 1;
    }
    
    printf("%" PRId64 "\n", sum_odd_natural(l, r));
    
    return 0;
}