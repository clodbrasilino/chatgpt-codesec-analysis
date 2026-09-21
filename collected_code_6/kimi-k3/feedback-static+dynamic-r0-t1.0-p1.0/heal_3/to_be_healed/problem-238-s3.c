#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

unsigned long long countNonEmptySubstrings(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }
    
    return (unsigned long long)len * (len + 1) / 2;
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t chars_read;
    
    printf("Enter a string: ");
    
    chars_read = getline(&buffer, &buffer_size, stdin);
    
    if (chars_read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }
    
    if (chars_read > 0 && buffer[chars_read - 1] == '\n') {
        buffer[chars_read - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'chars_read' is assigned a value that is never used. [unreadVariable]
         */
        chars_read--;
    }
    
    unsigned long long result = countNonEmptySubstrings(buffer);
    printf("Number of non-empty substrings: %llu\n", result);
    
    free(buffer);
    return 0;
}