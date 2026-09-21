#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

int64_t nth_octagonal_number(int64_t n) {
    if (n > 0) {
        int64_t n_squared = n * n;
        if (n_squared / n == n) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 3 * 4938271603950617284 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:13530,execs:5545,op:havoc,rep:9)
             */
            int64_t three_n_squared = 3 * n_squared;
            if (three_n_squared / 3 == n_squared) {
                int64_t two_n = 2 * n;
                if (two_n / 2 == n) {
                    return three_n_squared - two_n;
                }
            }
        }
    }
    return 0;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:323,execs:155,op:havoc,rep:4; likely memory-safety defect
  */

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64, &n) != 1) {
        return 1;
    }
    int64_t result = nth_octagonal_number(n);
    printf("The %" PRId64 "th octagonal number is: %" PRId64 "\n", n, result);
    return 0;
}