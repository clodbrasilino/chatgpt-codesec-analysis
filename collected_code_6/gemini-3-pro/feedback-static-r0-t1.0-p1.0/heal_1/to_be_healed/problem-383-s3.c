#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t toggle_odd_bits(uint32_t num) {
    uint32_t mask = 0xAAAAAAAA;
    return num ^ mask;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'num' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 'num' can be reduced. [variableScope]
     */
    uint32_t num = 0;
    /* Possible weaknesses found:
     *  Variable 'result' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 'result' can be reduced. [variableScope]
     */
    uint32_t result = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char *endptr;
        unsigned long val = strtoul(buffer, &endptr, 10);
        
        if (endptr != buffer && *endptr == '\n') {
            num = (uint32_t)val;
            result = toggle_odd_bits(num);
            printf("%u\n", result);
        } else {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    } else {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}