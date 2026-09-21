#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

unsigned int count_set_bits(uint32_t number) {
    unsigned int count = 0;
    while (number != 0) {
        number &= (number - 1);
        count++;
    }
    return count;
}

int main(void) {
    uint32_t input;
    int scan_result;
    
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    scan_result = scanf("%" SCNu32, &input);
    
    if (scan_result != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("%u\n", count_set_bits(input));
    
    return 0;
}