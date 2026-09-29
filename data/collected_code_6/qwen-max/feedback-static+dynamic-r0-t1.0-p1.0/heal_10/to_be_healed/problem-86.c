#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7, got <no output>
  *  test case 2 failed: expected 217, got <no output>
  *  test case 0 failed: expected 271, got <no output>
  */

int64_t centered_hexagonal_number(int64_t n) {
    if (n <= 0 || n > INT64_MAX / 3) {
        return -1;
    }
    int64_t result = (3 * n - 3) * n + 1;
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000004,time:1239,execs:348,op:quick,pos:10; likely memory-safety defect
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
    int64_t result = centered_hexagonal_number(n);
    if (result == -1) {
        printf("Invalid input. The number is too large.\n");
    } else {
        printf("The %" PRId64 "th centered hexagonal number is: %" PRId64 "\n", n, result);
    }
    return 0;
}