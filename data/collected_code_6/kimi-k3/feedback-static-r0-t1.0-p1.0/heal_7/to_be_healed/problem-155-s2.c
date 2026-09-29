#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t toggle_even_bits(uint32_t num) {
    return num ^ 0xAAAAAAAAu;
}

int main(void) {
    uint32_t num;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[32];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (sscanf(buffer, "%" SCNu32, &num) != 1) {
        return 1;
    }
    
    printf("%" PRIu32 "\n", toggle_even_bits(num));
    
    return 0;
}