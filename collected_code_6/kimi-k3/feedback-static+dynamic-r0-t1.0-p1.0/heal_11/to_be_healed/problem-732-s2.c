#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void replace_chars(char *str, size_t max_len) {
    size_t i;
    
    if (str == NULL || max_len == 0) {
        return;
    }
    
    for (i = 0; i < max_len && str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
    }
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ssize_t read;
    /* Possible weaknesses found:
     *  The scope of the variable 'len' can be reduced. [variableScope]
     */
    size_t len;

    read = getline(&buffer, &buffer_size, stdin);
    if (read == -1) {
        free(buffer);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    if (buffer != NULL && read > 0) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        len = strnlen(buffer, (size_t)read);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (len < (size_t)read) {
            buffer[len] = '\0';
        }
    }

    if (buffer != NULL) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        replace_chars(buffer, (size_t)read);
        printf("%s\n", buffer);
    }

    free(buffer);
    return 0;
}