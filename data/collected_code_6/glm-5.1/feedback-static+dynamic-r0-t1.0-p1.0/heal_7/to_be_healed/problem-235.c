#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t set_even_bits(uint32_t num) {
    uint32_t mask = 0x55555555;
    return num | mask;
}

int main(void) {
    uint32_t input = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[16];
    /* Possible weaknesses found:
     * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (fgets(buffer, sizeof(buffer), stdin) && sscanf(buffer, "%" SCNu32, &input) == 1) {
        uint32_t result = set_even_bits(input);
        printf("%" PRIu32 "\n", result);
    } else {
        return 1;
    }
    return 0;
}