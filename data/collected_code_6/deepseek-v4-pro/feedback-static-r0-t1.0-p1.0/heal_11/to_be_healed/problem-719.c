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
    
    size_t i = 1;
    while (str[i] != '\0') {
        if (str[i] != 'b') {
            return false;
        }
        i++;
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
    
    size_t len = 0;
    while (len < sizeof(input) && input[len] != '\0') {
        len++;
    }
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    
    if (match_pattern(input)) {
        printf("Match\n");
    } else {
        printf("No match\n");
    }
    
    return 0;
}