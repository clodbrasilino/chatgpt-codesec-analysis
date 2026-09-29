#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *extract_quoted(const char *input) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(input);
    char *buffer = (char *)malloc(length + 1);
    if (buffer == NULL) {
        return NULL;
    }
    
    int in_quote = 0;
    int index = 0;
    
    for (size_t i = 0; i < length; ++i) {
        if (input[i] == '\"') {
            in_quote = !in_quote;
            continue;
        }
        
        if (in_quote) {
            buffer[index++] = input[i];
        }
    }
    
    buffer[index] = '\0';
    
    if (index == 0) {
        free(buffer);
        return NULL;
    }
    
    char *result = (char *)malloc(index + 1);
    if (result == NULL) {
        free(buffer);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, buffer, index);
    result[index] = '\0';
    
    free(buffer);
    return result;
}

int main() {
    const char *test_string = "This is a \"sample\" test with multiple \"values\" quoted.";
    char *extracted = extract_quoted(test_string);
    
    if (extracted != NULL) {
        printf("Extracted: %s\n", extracted);
        free(extracted);
    } else {
        printf("No values found or allocation failed.\n");
    }
    
    return 0;
}