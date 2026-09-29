#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t sum_odd_natural_numbers(uint64_t l, uint64_t r) {
    if (l > r) {
        return 0;
    }
    
    uint64_t first_odd = (l % 2 == 0) ? l + 1 : l;
    
    if (first_odd > r) {
        return 0;
    }
    
    uint64_t last_odd = (r % 2 == 0) ? r - 1 : r;
    uint64_t count = (last_odd - first_odd) / 2 + 1;
    
    return count * (first_odd + last_odd) / 2;
}

int main(void) {
    uint64_t l, r;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (sscanf(buffer, "%" SCNu64 " %" SCNu64, &l, &r) != 2) {
        return 1;
    }
    
    printf("%" PRIu64 "\n", sum_odd_natural_numbers(l, r));
    
    return 0;
}