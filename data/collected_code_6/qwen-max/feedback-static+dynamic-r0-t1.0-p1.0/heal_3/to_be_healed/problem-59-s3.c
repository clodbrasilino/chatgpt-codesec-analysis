#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t nth_octagonal_number(int64_t n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3 * 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:1425,execs:608,op:havoc,rep:2)
     * UBSan: signed integer overflow: 2 * 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:1425,execs:608,op:havoc,rep:2)
     * UBSan: signed integer overflow: 166666666666665 * 55555555555555 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:1057,execs:450,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223372036854775805 * 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:1425,execs:608,op:havoc,rep:2)
     */
    return 3 * n * n - 2 * n;
}

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