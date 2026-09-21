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
    
    int64_t sum_first_last;
    if (first_odd <= INT64_MAX - last_odd) {
        sum_first_last = first_odd + last_odd;
    } else {
        int64_t diff = last_odd - first_odd;
        if (diff % 2 == 0) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 4611686018427387903 * 4611686018427387905 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:7661,execs:2476,op:havoc,rep:1)
             */
            return count * (first_odd + diff / 2);
        } else {
            return (count / 2) * (first_odd + last_odd) + (count % 2) * ((first_odd + last_odd) / 2);
        }
    }
    
    if (count % 2 == 0) {
        return (count / 2) * sum_first_last;
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 277777777777777 * 277777777777779 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000006,time:9083,execs:2980,op:havoc,rep:2)
         */
        return count * (sum_first_last / 2);
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:486,execs:183,op:havoc,rep:5; likely memory-safety defect
  */

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