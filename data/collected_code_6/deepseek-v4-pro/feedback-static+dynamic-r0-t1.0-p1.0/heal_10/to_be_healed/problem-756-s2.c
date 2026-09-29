#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static bool match_pattern(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    size_t len = strnlen(str, 256);
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
    char input[257] = {0};
    size_t input_len;
    bool overflow = false;
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    input_len = strnlen(input, sizeof(input));
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        input_len--;
    } else {
        overflow = true;
    }
    
    if (overflow) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return 1;
    }
    
    if (input_len >= 256) {
        return 1;
    }
    
    if (match_pattern(input)) {
        printf("Match\n");
    } else {
        printf("No match\n");
    }
    
    return 0;
}