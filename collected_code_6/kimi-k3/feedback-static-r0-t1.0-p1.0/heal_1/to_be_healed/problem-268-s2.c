#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t star_number(uint64_t n) {
    return 6 * n * (n - 1) + 1;
}

int main(void) {
    uint64_t n;
    
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &n) != 1) {
        return 1;
    }
    
    if (n == 0) {
        return 1;
    }
    
    printf("%" PRIu64 "\n", star_number(n));
    
    return 0;
}