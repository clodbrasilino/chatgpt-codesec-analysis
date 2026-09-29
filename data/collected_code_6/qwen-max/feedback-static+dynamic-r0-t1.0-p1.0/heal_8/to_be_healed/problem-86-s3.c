#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7, got <no output>
  *  test case 2 failed: expected 217, got <no output>
  *  test case 0 failed: expected 271, got <no output>
  */

int64_t nth_centered_hexagonal_number(int64_t n) {
    if (n > (INT64_MAX - 1) / 3 + 1 || n < 1) {
        fprintf(stderr, "Input value out of valid range for int64_t.\n");
        return -1;
    }
    int64_t temp = 3 * n;
    if (temp < 0) {
        fprintf(stderr, "Overflow detected.\n");
        return -1;
    }
    int64_t temp2 = n - 1;
    int64_t result = temp * temp2 + 1;
    if (result < 0) {
        fprintf(stderr, "Overflow detected.\n");
        return -1;
    }
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000004,time:833,execs:256,op:havoc,rep:15; likely memory-safety defect
  */

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[20];
    /* Possible weaknesses found:
     * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (fgets(input, sizeof(input), stdin) == NULL || sscanf(input, "%" SCNd64, &n) != 1 || n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }
    int64_t result = nth_centered_hexagonal_number(n);
    if (result == -1) {
        return 1;
    }
    printf("The %" PRIu64 "th centered hexagonal number is: %" PRIu64 "\n", n, result);
    return 0;
}