#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void find_lowercase_underscore_sequences(const char *str) {
    if (str == NULL) {
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    size_t i = 0;
    
    while (i < len) {
        if (islower((unsigned char)str[i])) {
            size_t start = i;
            
            while (i < len && (islower((unsigned char)str[i]) || str[i] == '_')) {
                i++;
            }
            
            size_t end = i;
            
            if (end > start + 1 && str[end - 1] != '_') {
                printf("%.*s\n", (int)(end - start), str + start);
            }
        } else {
            i++;
        }
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        
        find_lowercase_underscore_sequences(input);
    }
    
    return 0;
}