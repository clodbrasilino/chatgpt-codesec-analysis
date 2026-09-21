#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool match_pattern(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    size_t len = 0;
    while (len < 256 && str[len] != '\0') {
        len++;
    }
    
    if (len == 0 || len >= 256) {
        return false;
    }
    
    if (str[0] != 'a') {
        return false;
    }
    
    if (len == 1) {
        return true;
    }
    
    if (len == 2) {
        return str[1] == 'b';
    }
    
    return false;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[257];
    bool input_valid = false;
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    size_t newline_pos = 0;
    bool newline_found = false;
    while (newline_pos < sizeof(input) && input[newline_pos] != '\0') {
        if (input[newline_pos] == '\n') {
            input[newline_pos] = '\0';
            newline_found = true;
            input_valid = true;
            break;
        }
        newline_pos++;
    }
    
    if (!newline_found && newline_pos == sizeof(input) - 1) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        input[sizeof(input) - 1] = '\0';
        input_valid = true;
    }
    
    if (!input_valid) {
        return 1;
    }
    
    size_t length = 0;
    while (length < sizeof(input) && input[length] != '\0') {
        length++;
    }
    
    if (length >= 256) {
        printf("No match\n");
        return 0;
    }
    
    if (match_pattern(input)) {
        printf("Match\n");
    } else {
        printf("No match\n");
    }
    
    return 0;
}