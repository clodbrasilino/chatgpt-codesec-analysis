#include <stdio.h>
#include <string.h>
#include <ctype.h>

int binary_to_decimal(const char *binary) {
    int decimal = 0;
    size_t i = 0;
    
    while (binary[i] != '\0') {
        if (binary[i] != '0' && binary[i] != '1') {
            return -1;
        }
        
        decimal = decimal * 2 + (binary[i] - '0');
        i++;
    }
    
    if (i == 0) {
        return -1;
    }
    
    return decimal;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[65] = {0};
    
    printf("Enter a binary number: ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    else if (len + 1 >= sizeof(input)) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Input too long\n");
        return 1;
    }
    
    int result = binary_to_decimal(input);
    
    if (result == -1) {
        printf("Invalid binary number\n");
        return 1;
    }
    
    printf("Decimal equivalent: %d\n", result);
    
    return 0;
}