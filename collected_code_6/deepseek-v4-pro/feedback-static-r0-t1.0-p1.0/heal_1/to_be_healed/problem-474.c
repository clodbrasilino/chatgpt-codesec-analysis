#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_char(char *str, char old_char, char new_char) {
    if (str == NULL) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(str);
    char *result = (char *)malloc(length + 1);
    
    if (result == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < length; i++) {
        if (str[i] == old_char) {
            result[i] = new_char;
        } else {
            result[i] = str[i];
        }
    }
    
    result[length] = '\0';
    return result;
}

int main(void) {
    char input[] = "hello world";
    char old_char = 'o';
    char new_char = '0';
    
    char *result = replace_char(input, old_char, new_char);
    
    if (result != NULL) {
        printf("Original: %s\n", input);
        printf("Modified: %s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}