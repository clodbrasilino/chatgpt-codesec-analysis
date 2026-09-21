#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <stdlib.h>

int64_t nth_octagonal_number(int64_t n) {
    if (n > 0 && n <= (INT64_MAX / 3)) {
        int64_t n_squared = n * n;
        if ((n_squared / n) == n) {
            if (n_squared > (INT64_MAX / 3)) {
                return 0;
            }
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

int get_input(int64_t *n) {
    char *input = NULL;
    size_t len = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ssize_t read;

    /* Possible weaknesses found:
     *  Variable 'read' is assigned a value that is never used. [unreadVariable]
     *  Although the value stored to 'read' is used in the enclosing expression, the value is never actually read from 'read' [deadcode.DeadStores]
     */
    if ((read = getline(&input, &len, stdin)) == -1) {
        free(input);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (sscanf(input, "%" SCNd64, n) != 1) {
        free(input);
        return 1;
    }

    free(input);
    return 0;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:440,execs:153,op:havoc,rep:8; likely memory-safety defect
  */

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (get_input(&n) != 0) {
        return 1;
    }
    int64_t result = nth_octagonal_number(n);
    printf("The %" PRId64 "th octagonal number is: %" PRId64 "\n", n, result);
    return 0;
}