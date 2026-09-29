#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

uint64_t sum_fourth_power_even(uint32_t n) {
    uint64_t sum = 0;
    uint32_t i;
    for (i = 1; i <= n; i++) {
        uint64_t even_num = (uint64_t)2 * i;
        uint64_t fourth_power = even_num * even_num * even_num * even_num;
        sum += fourth_power;
    }
    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[128];
    char *end_ptr;
    uint32_t n = 0;
    int valid_input = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'len' can be reduced. [variableScope]
     */
    size_t len;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'has_digits' can be reduced. [variableScope]
     */
    int has_digits = 0;
    
    printf("Enter the value of n: ");
    
    if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        len = strlen(input_buffer);
        
        if (len > 0 && len < sizeof(input_buffer) - 1) {
            if (input_buffer[len - 1] == '\n') {
                input_buffer[len - 1] = '\0';
                len--;
            }
            
            if (len > 0) {
                for (i = 0; i < len; i++) {
                    if (!isdigit((unsigned char)input_buffer[i])) {
                        valid_input = 0;
                        break;
                    }
                    has_digits = 1;
                }
                
                if (has_digits && (i == len)) {
                    errno = 0;
                    unsigned long temp_val = strtoul(input_buffer, &end_ptr, 10);
                    
                    if (end_ptr != input_buffer && 
                        *end_ptr == '\0' &&
                        errno != ERANGE && 
                        temp_val <= UINT32_MAX) {
                        n = (uint32_t)temp_val;
                        valid_input = 1;
                    }
                }
            }
        }
    }
    
    if (!valid_input) {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    printf("Sum of fourth power of first %" PRIu32 " even natural numbers: %" PRIu64 "\n", 
           n, sum_fourth_power_even(n));
    
    return 0;
}