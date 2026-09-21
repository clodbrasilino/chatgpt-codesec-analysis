#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t nth_rectangular_number(int64_t n) {
    if (n > INT64_MAX / (n + 1)) {
        fprintf(stderr, "Overflow detected\n");
        return -1;
    }
    int64_t result = n * (n + 1);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000004,time:843,execs:291,op:havoc,rep:8; likely memory-safety defect
  */

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64, &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (n < 1) {
        fprintf(stderr, "n must be a positive integer\n");
        return 1;
    }
    int64_t result = nth_rectangular_number(n);
    if (result == -1) {
        return 1;
    }
    printf("The %" PRId64 "-th rectangular number is: %" PRId64 "\n", n, result);
    return 0;
}