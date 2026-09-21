#include <stdio.h>
#include <stdlib.h>

char *extract_quoted(const char *input) {
    size_t length = 0;
    while (input[length] && input[length] != '\"') length++;
    if (input[length] == '\"') length++;
    
    for (; input[length]; ++length) {
        if (input[length] == '\"' && (length == 0 || input[length - 1] != '\\')) {
            break;
        }
    }
    
    char *buffer = (char *)malloc(length + 1);
    if (buffer == NULL) {
        return NULL;
    }
    
    size_t index = 0;
    int in_quote = 0;
    
    for (size_t i = 0; i < length; ++i) {
        if (input[i] == '\"' && (i == 0 || input[i - 1] != '\\')) {
            in_quote = !in_quote;
            continue;
        }
        
        if (in_quote && input[i] != '"') {
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
    
    for (size_t i = 0; i <= index; ++i) {
        result[i] = buffer[i];
    }
    
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