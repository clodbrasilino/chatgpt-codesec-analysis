#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool contains_z_not_at_edges(const char *word) {
    if (word == NULL) {
        return false;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(word);
    
    if (len < 3) {
        return false;
    }
    
    for (size_t i = 1; i < len - 1; i++) {
        if (word[i] == 'z' || word[i] == 'Z') {
            return true;
        }
    }
    
    return false;
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ssize_t read;
    
    read = getline(&buffer, &buffer_size, stdin);
    
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    if (read != -1) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (read > 0 && buffer[read - 1] == '\n') {
            buffer[read - 1] = '\0';
        }
        
        if (contains_z_not_at_edges(buffer)) {
            printf("Match\n");
        } else {
            printf("No match\n");
        }
        
        free(buffer);
    }
    
    return 0;
}