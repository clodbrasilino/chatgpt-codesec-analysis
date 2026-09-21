#include <stdio.h>
#include <string.h>
#include <ctype.h>

int match_word_with_z(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }
    
    size_t start = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'end' can be reduced. [variableScope]
     *  Variable 'end' is assigned a value that is never used. [unreadVariable]
     */
    size_t end = 0;
    
    while (start < len) {
        while (start < len && !isalpha((unsigned char)str[start])) {
            start++;
        }
        
        if (start >= len) {
            break;
        }
        
        end = start;
        int has_z = 0;
        
        while (end < len && isalpha((unsigned char)str[end])) {
            if (str[end] == 'z' || str[end] == 'Z') {
                has_z = 1;
            }
            end++;
        }
        
        if (has_z) {
            return 1;
        }
        
        start = end;
    }
    
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
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