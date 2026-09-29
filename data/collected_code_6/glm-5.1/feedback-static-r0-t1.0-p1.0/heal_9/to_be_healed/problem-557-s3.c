#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void toggle_case(char *str, size_t len) {
    if (str == NULL) {
        return;
    }
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)str[i])) {
            str[i] = tolower((unsigned char)str[i]);
        } else if (islower((unsigned char)str[i])) {
            str[i] = toupper((unsigned char)str[i]);
        }
    }
}

int main(void) {
    char *buffer = NULL;
    size_t len = 0;
    ssize_t read = getline(&buffer, &len, stdin);
    
    if (read == -1) {
        free(buffer);
        return 1;
    }
    
    /* Possible weaknesses found:
     *  Variable 'safe_len' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 'safe_len' can be reduced. [variableScope]
     */
    size_t safe_len = 0;
    
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    if (read > 0) {
        if (buffer[read - 1] == '\n') {
            buffer[read - 1] = '\0';
            read--;
        }
        
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (read > 0) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            safe_len = strnlen(buffer, (size_t)read);
            toggle_case(buffer, safe_len);
            printf("%s\n", buffer);
        }
    }
    
    free(buffer);
    return 0;
}