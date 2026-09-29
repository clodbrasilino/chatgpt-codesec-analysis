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
    size_t len;
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    
    if (len >= sizeof(input) - 1) {
        return 1;
    }
    
    if (match_pattern(input)) {
        printf("Match\n");
    } else {
        printf("No match\n");
    }
    
    return 0;
}