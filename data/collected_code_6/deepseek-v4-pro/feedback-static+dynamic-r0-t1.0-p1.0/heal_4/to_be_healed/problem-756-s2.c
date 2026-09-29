#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool match_pattern(const char *str) {
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
    char input[257];
    size_t input_len;
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    input_len = strnlen(input, sizeof(input));
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