#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <stdlib.h>
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
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000006,time:4996,execs:1322,op:havoc,rep:4; likely memory-safety defect
  */

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[20];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Failed to read input.\n");
        return 1;
    }
    char *endptr;
    n = strtoll(input, &endptr, 10);
    if (*endptr != '\n' || n <= 0 || endptr == input || n > (INT64_MAX - 1) / 3 + 1) {
        printf("Please enter a positive integer within the valid range.\n");
        return 1;
    }
    int64_t result = nth_centered_hexagonal_number(n);
    if (result == -1) {
        return 1;
    }
    printf("The %" PRIu64 "th centered hexagonal number is: %" PRIu64 "\n", n, result);
    return 0;
}