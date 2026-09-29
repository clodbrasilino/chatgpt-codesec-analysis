#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

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
    printf("The %" PRIu64 "th tetrahedral number is: %" PRIu64 "\n", n, nth_tetrahedral_number(n));
    return 0;
}