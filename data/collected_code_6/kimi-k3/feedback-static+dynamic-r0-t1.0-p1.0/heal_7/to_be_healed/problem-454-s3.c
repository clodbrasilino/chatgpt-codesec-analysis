#include <stdio.h>
#include <string.h>
#include <ctype.h>

int match_word_with_z(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    size_t start = 0;
    
    while (str[start] != '\0') {
        while (str[start] != '\0' && !isalpha((unsigned char)str[start])) {
            start++;
        }
        
        if (str[start] == '\0') {
            break;
        }
        
        int has_z = 0;
        
        while (str[start] != '\0' && isalpha((unsigned char)str[start])) {
            if (str[start] == 'z' || str[start] == 'Z') {
                has_z = 1;
            }
            start++;
        }
        
        if (has_z) {
            return 1;
        }
    }
    
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    buffer[sizeof(buffer) - 1] = '\0';
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    if (match_word_with_z(buffer)) {
        printf("Match found\n");
    } else {
        printf("No match\n");
    }
    
    return 0;
}