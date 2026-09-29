#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
/* Possible weaknesses found:
 *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
 */
#include <stdint.h>

int count_same_position(const char *str) {
    int count = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  'INT_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'INT_MAX'
         */
        if (i > INT_MAX) {
            break;
        }
        
        if (isalpha((unsigned char)str[i])) {
            char lower = tolower((unsigned char)str[i]);
            if (lower - 'a' == (int)i) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    char *input = NULL;
    size_t len = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ssize_t read;
    
    printf("Enter a string: ");
    
    if (ferror(stdin) || feof(stdin)) {
        return 1;
    }
    
    read = getline(&input, &len, stdin);
    
    if (read == -1) {
        free(input);
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
    }
    
    int result = count_same_position(input);
    printf("Count: %d\n", result);
    
    free(input);
    input = NULL;
    return 0;
}