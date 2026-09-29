#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

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
    uint32_t n;
    int scan_result;
    
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    scan_result = scanf("%" SCNu32, &n);
    
    if (scan_result != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    printf("Sum of fourth power of first %" PRIu32 " even natural numbers: %" PRIu64 "\n", 
           n, sum_fourth_power_even(n));
    
    return 0;
}