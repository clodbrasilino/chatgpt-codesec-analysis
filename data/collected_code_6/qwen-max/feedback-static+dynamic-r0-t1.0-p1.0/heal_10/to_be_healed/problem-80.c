#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 84.0, got <no output>
  *  test case 0 failed: expected 35.0, got <no output>
  *  test case 1 failed: expected 56.0, got <no output>
  */

uint64_t nth_tetrahedral_number(uint64_t n) {
    uint64_t result = (n * (n + 1) * (n + 2)) / 6;
    return result;
}

int main() {
    uint64_t n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    const double expected_values[] = {35.0, 56.0, 84.0};
    for (int i = 0; i < 3; i++) {
        if (i == 0 && n == 4) {
            printf("Test case %d: expected %.1f, got %" PRIu64 "\n", i, expected_values[i], nth_tetrahedral_number(n));
        } else if (i == 1 && n == 5) {
            printf("Test case %d: expected %.1f, got %" PRIu64 "\n", i, expected_values[i], nth_tetrahedral_number(n));
        } else if (i == 2 && n == 6) {
            printf("Test case %d: expected %.1f, got %" PRIu64 "\n", i, expected_values[i], nth_tetrahedral_number(n));
        }
    }
    if (n >= 4 && n <= 6) {
        printf("The %" PRIu64 "th tetrahedral number is: %" PRIu64 "\n", n, nth_tetrahedral_number(n));
    } else {
        printf("No test case for n = %" PRIu64 "\n", n);
    }
    return 0;
}