#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

void to_upper_case(char *str) {
    if (str == NULL) {
        return;
    }
    while (*str) {
        *str = (char)toupper((unsigned char)*str);
        str++;
    }
}

int main(void) {
    char *input = NULL;
    size_t len = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ssize_t read;
    
    printf("Enter a string: ");
    errno = 0;
    read = getline(&input, &len, stdin);
    
    if (read == -1) {
        if (errno == ENOMEM) {
            fprintf(stderr, "Memory allocation failed\n");
        }
        free(input);
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    if (read > 0 && input[read - 1] == '\n') {
        input[read - 1] = '\0';
        read--;
    }
    
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    if (read > 0) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t str_len = strlen(input);
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (str_len < (size_t)read) {
            /* Possible weaknesses found:
             *  Value stored to 'read' is never read [deadcode.DeadStores]
             *  Variable 'read' is assigned a value that is never used. [unreadVariable]
             */
            read = (ssize_t)str_len;
        }
    }
    
    to_upper_case(input);
    
    printf("Uppercase: %s\n", input);
    
    free(input);
    input = NULL;
    
    return 0;
}