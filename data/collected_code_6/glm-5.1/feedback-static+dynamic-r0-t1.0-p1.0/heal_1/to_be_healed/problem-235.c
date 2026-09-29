#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t set_even_bits(uint32_t num) {
    uint32_t mask = 0;
    for (int i = 0; i < 32; i += 2) {
        mask |= (1U << i);
    }
    return num | mask;
}

int main(void) {
    uint32_t input = 0;
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    int ret = scanf("%" SCNu32, &input);
    if (ret == 1) {
        uint32_t result = set_even_bits(input);
        printf("%" PRIu32 "\n", result);
    } else {
        return 1;
    }
    return 0;
}