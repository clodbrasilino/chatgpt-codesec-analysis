#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_pattern(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    if (str[0] == '\0') {
        return false;
    }
    
    if (str[0] != 'a') {
        return false;
    }
    
    const char *ptr = str + 1;
    while (*ptr != '\0') {
        if (*ptr != 'b') {
            return false;
        }
        ptr++;
    }
    
    return true;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    int has_newline = 0;
    for (size_t i = 0; i < sizeof(input); i++) {
        if (input[i] == '\n') {
            input[i] = '\0';
            has_newline = 1;
            break;
        }
        if (input[i] == '\0') {
            break;
        }
    }
    
    if (!has_newline && input[0] != '\0') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    
    if (input[0] == '\0') {
        return 1;
    }
    
    if (match_pattern(input)) {
        printf("Match\n");
    } else {
        printf("No match\n");
    }
    
    return 0;
}