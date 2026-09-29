#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>

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
    char input_buffer[64];
    char *end_ptr;
    uint32_t n = 0;
    int valid_input = 0;
    
    printf("Enter the value of n: ");
    
    if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
        errno = 0;
        unsigned long temp_val = strtoul(input_buffer, &end_ptr, 10);
        
        if (end_ptr != input_buffer && 
            (*end_ptr == '\n' || *end_ptr == '\0') &&
            errno != ERANGE && 
            temp_val <= UINT32_MAX) {
            n = (uint32_t)temp_val;
            valid_input = 1;
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