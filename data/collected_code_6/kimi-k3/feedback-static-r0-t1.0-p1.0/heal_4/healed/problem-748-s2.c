#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* add_spaces_before_capitals(const char* input, size_t input_len) {
    char* result;
    size_t result_len;
    size_t result_capacity;
    size_t i;
    
    if (input == NULL) {
        return NULL;
    }
    
    result_capacity = input_len * 2 + 1;
    result = malloc(result_capacity);
    if (result == NULL) {
        return NULL;
    }
    
    result_len = 0;
    
    for (i = 0; i < input_len; i++) {
        if (input[i] >= 'A' && input[i] <= 'Z') {
            if (result_len > 0) {
                if (result_len + 2 > result_capacity) {
                    size_t new_capacity = result_capacity * 2;
                    char* temp = realloc(result, new_capacity);
                    if (temp == NULL) {
                        free(result);
                        return NULL;
                    }
                    result = temp;
                    result_capacity = new_capacity;
                }
                result[result_len++] = ' ';
            }
        }
        
        if (result_len + 2 > result_capacity) {
            size_t new_capacity = result_capacity * 2;
            char* temp = realloc(result, new_capacity);
            if (temp == NULL) {
                free(result);
                return NULL;
            }
            result = temp;
            result_capacity = new_capacity;
        }
        
        result[result_len++] = input[i];
    }
    
    result[result_len] = '\0';
    
    return result;
}

int main(void) {
    const char test_string[] = "HelloWorldThisIsATest";
    char* result;
    size_t test_len;
    
    test_len = sizeof(test_string) - 1;
    result = add_spaces_before_capitals(test_string, test_len);
    
    if (result == NULL) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }
    
    printf("Original: %s\n", test_string);
    printf("Modified: %s\n", result);
    
    free(result);
    
    return EXIT_SUCCESS;
}