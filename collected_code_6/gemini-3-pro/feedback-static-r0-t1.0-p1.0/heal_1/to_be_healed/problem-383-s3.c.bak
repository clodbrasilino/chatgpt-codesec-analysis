#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t toggle_odd_bits(uint32_t num) {
    uint32_t mask = 0xAAAAAAAA;
    return num ^ mask;
}

int main(void) {
    /* Possible weaknesses found:
     *  The scope of the variable 'num' can be reduced. [variableScope]
     *  Variable 'num' is assigned a value that is never used. [unreadVariable]
     */
    uint32_t num = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'result' can be reduced. [variableScope]
     *  Variable 'result' is assigned a value that is never used. [unreadVariable]
     */
    uint32_t result = 0;
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