#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t star_number(uint64_t n) {
    return 6 * n * (n - 1) + 1;
}

int main(void) {
    uint64_t n;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buf[32];
    
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (sscanf(buf, "%" SCNu64, &n) != 1) {
        return 1;
    }
    
    if (n == 0) {
        return 1;
    }
    
    printf("%" PRIu64 "\n", star_number(n));
    
    return 0;
}