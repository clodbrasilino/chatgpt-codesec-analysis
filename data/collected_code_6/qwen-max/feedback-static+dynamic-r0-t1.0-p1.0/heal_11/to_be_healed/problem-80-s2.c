#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 84.0, got <no output>
  *  test case 0 failed: expected 35.0, got <no output>
  *  test case 1 failed: expected 56.0, got <no output>
  */

uint64_t nth_tetrahedral_number(uint64_t n) {
    return (n * (n + 1) * (n + 2)) / 6;
}

int main() {
    uint64_t n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    int scan_result = scanf("%" SCNu64, &n);
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (getchar() != '\n' && scan_result == 1);
    /* Possible weaknesses found:
     *  Checking if unsigned expression 'n' is less than zero. [unsignedLessThanZero]
     */
    if (scan_result != 1 || n < 0) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (getchar() != '\n');
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return 1;
    }
    uint64_t result = nth_tetrahedral_number(n);
    printf("The %" PRIu64 "th tetrahedral number is: %" PRIu64 "\n", n, result);
    return 0;
}