#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <limits.h>

int64_t nth_hexagonal_number(int64_t n) {
    if (n < 1 || n > 3037000499) {
        return -1;
    }
    int64_t max_safe_n = (INT64_MAX / n + 1) / 2;
    if (n > max_safe_n) {
        return -1;
    }
    int64_t result = n * (2 * n - 1);
    if (result / n != 2 * n - 1) {
        return -1;
    }
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000004,time:1066,execs:335,op:quick,pos:1; likely memory-safety defect
  */

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64, &n) == 1 && n > 0) {
        int64_t hex_num = nth_hexagonal_number(n);
        if (hex_num == -1) {
            printf("Invalid input or integer overflow occurred. Please enter a smaller positive integer.\n");
        } else {
            printf("The %" PRId64 "th hexagonal number is: %" PRId64 "\n", n, hex_num);
        }
    } else {
        printf("Invalid input. Please enter a positive integer.\n");
    }
    return 0;
}