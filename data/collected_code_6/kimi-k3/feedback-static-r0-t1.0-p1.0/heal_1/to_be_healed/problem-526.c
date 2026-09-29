#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int capitalize_first_last(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len >= size) {
        return -1;
    }
    
    size_t i = 0;
    while (i < len) {
        if (!isspace((unsigned char)str[i])) {
            size_t start = i;
            size_t end = i;
            
            while (end < len && !isspace((unsigned char)str[end])) {
                end++;
            }
            
            if (end > start) {
                str[start] = (char)toupper((unsigned char)str[start]);
                if (end - 1 > start) {
                    str[end - 1] = (char)toupper((unsigned char)str[end - 1]);
                }
            }
            
            i = end;
        } else {
            i++;
        }
    }
    
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    if (capitalize_first_last(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }
    
    printf("Result: %s\n", buffer);
    
    return EXIT_SUCCESS;
}