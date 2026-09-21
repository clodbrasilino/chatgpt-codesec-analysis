#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_non_alphanumeric(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    size_t dst_pos = 0;
    for (size_t i = 0; i < len; i++) {
        if (isalnum((unsigned char)input[i])) {
            result[dst_pos++] = input[i];
        }
    }
    result[dst_pos] = '\0';
    
    char* trimmed = (char*)realloc(result, dst_pos + 1);
    if (trimmed != NULL) {
        result = trimmed;
    }
    
    return result;
}

int main(void) {
    const char* test_string = "Hello, World! 123 @#$%^&*()";
    char* cleaned = remove_non_alphanumeric(test_string);
    
    if (cleaned != NULL) {
        printf("Original: %s\n", test_string);
        printf("Cleaned: %s\n", cleaned);
        free(cleaned);
    } else {
        printf("Error processing string\n");
        return 1;
    }
    
    return 0;
}