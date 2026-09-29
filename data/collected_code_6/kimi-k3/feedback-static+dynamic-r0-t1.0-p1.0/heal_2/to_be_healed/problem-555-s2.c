#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t compute_difference(int64_t n) {
    if (n < 0) {
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3333333333 * 3333333334 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000000,time:6145,execs:2087,op:havoc,rep:4)
     */
    int64_t sum = n * (n + 1) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -3667816480743664697 * -3667816480743664697 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000000,time:6145,execs:2087,op:havoc,rep:4)
     * UBSan: signed integer overflow: 3032474114169753 * 3032474114169753 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000000,time:7167,execs:2420,op:havoc,rep:14)
     */
    int64_t sum_of_cubes = sum * sum;
    return sum_of_cubes - sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:1429,execs:507,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    int64_t n;
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64, &n) != 1) {
        return 1;
    }
    printf("%" PRId64 "\n", compute_difference(n));
    return 0;
}