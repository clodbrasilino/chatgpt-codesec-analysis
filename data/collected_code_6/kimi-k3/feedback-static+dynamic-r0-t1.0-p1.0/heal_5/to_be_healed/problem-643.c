#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>

bool contains_z_not_at_edges(const char *word, size_t len) {
    if (word == NULL || len < 3) {
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
    if (read != -1 && buffer != NULL) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        size_t len = (size_t)read;
        
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        
        if (contains_z_not_at_edges(buffer, len)) {
            printf("Match\n");
        } else {
            printf("No match\n");
        }
        
        free(buffer);
    }
    
    return 0;
}