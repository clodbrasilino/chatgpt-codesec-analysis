#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int count_same_position(const char *str) {
    int count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    
    for (size_t i = 0; i < len; i++) {
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
    }
    
    int result = count_same_position(input);
    printf("Count: %d\n", result);
    
    free(input);
    return 0;
}