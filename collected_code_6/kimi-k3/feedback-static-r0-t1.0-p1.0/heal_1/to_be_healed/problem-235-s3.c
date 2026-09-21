#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t set_even_bits(uint32_t num) {
    uint32_t even_bits_mask = 0x55555555U;
    return num | even_bits_mask;
}

int main(void) {
    uint32_t number;
    int scan_result;

    printf("Enter a number (uint32_t): ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    scan_result = scanf("%" SCNu32, &number);

    if (scan_result != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    uint32_t result = set_even_bits(number);

    printf("Original number: %" PRIu32 "\n", number);
    printf("Number after setting even bits: %" PRIu32 "\n", result);

    return 0;
}