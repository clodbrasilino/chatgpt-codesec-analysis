#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void find_lowercase_underscore_sequences(const char *str, size_t max_len) {
    if (str == NULL) {
        return;
    }
    
    size_t len = strnlen(str, max_len);
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
        size_t len = strnlen(input, sizeof(input));
        
        if (len == sizeof(input) && input[len - 1] != '\n') {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) {
            }
        }
        
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        
        find_lowercase_underscore_sequences(input, sizeof(input));
    }
    
    return 0;
}