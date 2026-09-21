#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t next_perfect_square(uint64_t n) {
    uint64_t root = (uint64_t)sqrt(n);
    if (root * root == n) {
        root += 1;
    }
    return root * root;
}

int main() {
    uint64_t number;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &number) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    uint64_t next_square = next_perfect_square(number);
    printf("Next perfect square: %" PRIu64 "\n", next_square);
    return 0;
}