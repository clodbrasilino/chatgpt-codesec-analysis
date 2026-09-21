#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_multiple_spaces(const char* input) {
    char* result;
    size_t input_len;
    size_t result_len = 0;
    size_t i = 0;
    int in_space = 0;
    
    if (input == NULL) {
        return NULL;
    }
    
    input_len = strnlen(input, 4096);
    if (input_len == 4096 && input[4095] != '\0') {
        return NULL;
    }
    
    result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    while (i < input_len) {
        if (input[i] == ' ') {
            if (!in_space) {
                result[result_len] = ' ';
                result_len++;
                in_space = 1;
            }
        } else {
            result[result_len] = input[i];
            result_len++;
            in_space = 0;
        }
        i++;
    }
    
    result[result_len] = '\0';
    
    return result;
}

int main(void) {
    const char* test_string = "This   is    a     test    string   with    multiple     spaces.";
    char* cleaned_string;
    
    printf("Original: %s\n", test_string);
    
    cleaned_string = remove_multiple_spaces(test_string);
    
    if (cleaned_string == NULL) {
        fprintf(stderr, "Error: Failed to process string\n");
        return EXIT_FAILURE;
    }
    
    printf("Cleaned:  %s\n", cleaned_string);
    
    free(cleaned_string);
    
    return EXIT_SUCCESS;
}