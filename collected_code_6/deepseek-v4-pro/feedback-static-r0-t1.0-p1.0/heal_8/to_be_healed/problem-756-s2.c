#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PATTERN_LENGTH 255
#define INPUT_BUFFER_SIZE 258

bool match_pattern(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    size_t len = strnlen(str, MAX_PATTERN_LENGTH + 1);
    
    if (len == 0 || len > MAX_PATTERN_LENGTH) {
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
    char input[INPUT_BUFFER_SIZE];
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
    
    if (!newline_found) {
        if (newline_pos >= sizeof(input) - 1) {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) {
            }
        }
        if (sizeof(input) > 0) {
            input[sizeof(input) - 1] = '\0';
        }
        input_valid = true;
    }
    
    if (!input_valid) {
        return 1;
    }
    
    size_t length = strnlen(input, sizeof(input));
    
    if (length > MAX_PATTERN_LENGTH) {
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