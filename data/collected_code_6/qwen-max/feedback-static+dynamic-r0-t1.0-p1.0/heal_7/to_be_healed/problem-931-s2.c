#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <limits.h>

bool is_safe_multiply(int64_t a, int64_t b) {
    if (a > 0) {
        if (b > 0 && a > (INT64_MAX / b)) return false;
        if (b < 0 && -b > (INT64_MIN / a)) return false;
    } else if (a < 0) {
        if (b < 0 && -a > (INT64_MAX / -b)) return false;
        if (b > 0 && b > (INT64_MIN / a)) return false;
    }
    return true;
}

int64_t sum_of_cubes(int64_t n) {
    if (n <= 0) return 0;

    int64_t temp1 = n * n;
    if (!is_safe_multiply(n, n)) return 0;

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3086419691358025 * 55555556 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000001,time:3479,execs:1532,op:havoc,rep:5)
     */
    int64_t temp2 = temp1 * (n + 1);
    if (!is_safe_multiply(temp1, n + 1)) return 0;

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 470504923187050752 * 777777 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:3458,execs:1525,op:havoc,rep:5)
     */
    int64_t result = temp2 * (n + 1);
    if (!is_safe_multiply(temp2, n + 1)) return 0;

    if (result % 4 != 0) return 0;
    result /= 4;

    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:471,execs:217,op:havoc,rep:6; likely memory-safety defect
  */

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64, &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }

    int64_t result = sum_of_cubes(n);
    if (result == 0) {
        fprintf(stderr, "Overflow detected. Please enter a smaller value for n.\n");
        return EXIT_FAILURE;
    }

    printf("The sum of the series 1^3 + 2^3 + ... + %" PRId64 "^3 is %" PRId64 "\n", n, result);
    return EXIT_SUCCESS;
}