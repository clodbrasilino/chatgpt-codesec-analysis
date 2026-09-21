#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>

long binary_to_decimal(const char *binary, size_t max_len) {
    long decimal = 0;
    size_t len = 0;
    
    if (binary == NULL) {
        return -1;
    }
    
    while (len < max_len && binary[len] != '\0') {
        if (binary[len] != '0' && binary[len] != '1') {
            return -1;
        }
        len++;
    }
    
    if (len == 0) {
        return -1;
    }
    
    for (size_t i = 0; i < len; i++) {
        int digit = binary[i] - '0';
        
        if (decimal > LONG_MAX / 2) {
            return -1;
        }
        
        decimal = decimal * 2;
        
        if (decimal > LONG_MAX - digit) {
            return -1;
        }
        
        decimal += digit;
    }
    
    return decimal;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[65];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char format[8];
    
    snprintf(format, sizeof(format), "%%%zus", (size_t)(sizeof(input) - 1));
    
    printf("Enter a binary number: ");
    
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf(format, input) != 1) {
        printf("Error reading input\n");
        return 1;
    }
    
    input[sizeof(input) - 1] = '\0';
    
    long result = binary_to_decimal(input, sizeof(input));
    
    if (result == -1) {
        printf("Invalid binary number\n");
        return 1;
    }
    
    printf("Decimal equivalent: %ld\n", result);
    
    return 0;
}