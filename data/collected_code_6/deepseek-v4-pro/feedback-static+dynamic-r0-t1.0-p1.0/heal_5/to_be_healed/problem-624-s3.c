#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

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
        free(input);
        if (errno == ENOMEM) {
            return 1;
        }
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    if (read > 0 && input[read - 1] == '\n') {
        input[read - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'read' is assigned a value that is never used. [unreadVariable]
         */
        read--;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    } else if (read > 0 && (size_t)read < len) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        input[read] = '\0';
    }
    
    to_upper_case(input);
    
    printf("Uppercase: %s\n", input);
    
    free(input);
    return 0;
}