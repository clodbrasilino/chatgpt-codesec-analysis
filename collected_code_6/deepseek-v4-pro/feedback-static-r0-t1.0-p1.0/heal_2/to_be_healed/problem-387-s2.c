#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool is_hex_even(const char *hex_str) {
    if (hex_str == NULL || *hex_str == '\0') {
        return false;
    }
    
    size_t len = 0;
    /* Possible weaknesses found:
     *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
     */
    while (hex_str[len] != '\0' && len < 32) {
        if (!isxdigit((unsigned char)hex_str[len]) && hex_str[len] != '\n') {
            return false;
        }
        len++;
    }
    
    /* Possible weaknesses found:
     *  Assuming that condition 'len==0' is not redundant
     */
    if (len == 0) {
        return false;
    }
    
    /* Possible weaknesses found:
     *  Condition 'len>0' is always true [knownConditionTrueFalse]
     *  Condition 'len>0' is always true
     */
    if (len > 0 && hex_str[len - 1] == '\n') {
        len--;
    }
    
    if (len == 0) {
        return false;
    }
    
    char last_char = hex_str[len - 1];
    
    switch (last_char) {
        case '0': case '2': case '4': case '6': case '8':
        case 'A': case 'C': case 'E':
        case 'a': case 'c': case 'e':
            return true;
        case '1': case '3': case '5': case '7': case '9':
        case 'B': case 'D': case 'F':
        case 'b': case 'd': case 'f':
            return false;
        default:
            return false;
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t input_len = 0;
        /* Possible weaknesses found:
         *  Array index 'input_len' is used before limits check. [arrayIndexThenCheck]
         */
        while (input[input_len] != '\0' && input_len < sizeof(input)) {
            input_len++;
        }
        if (input_len > 0 && input[input_len - 1] == '\n') {
            input[input_len - 1] = '\0';
        }
        
        if (is_hex_even(input)) {
            printf("Even\n");
        } else {
            printf("Odd\n");
        }
    }
    
    return 0;
}