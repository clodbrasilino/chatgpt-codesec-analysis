#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t nth_decagonal_number(int64_t n) {
    if (n > 0 && n <= 9223372036854775807 / 4) {
        int64_t result = 4 * n * n - 3 * n;
        return result;
    }
    return 0;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000004,time:1548,execs:544,op:quick,pos:10; likely memory-safety defect
  */

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64, &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    int64_t result = nth_decagonal_number(n);
    if (result == 0) {
        fprintf(stderr, "Input too large for computation\n");
        return 1;
    }
    printf("The %" PRId64 "th decagonal number is: %" PRId64 "\n", n, result);
    return 0;
}