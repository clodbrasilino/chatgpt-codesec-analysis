#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* move_numbers_to_string(const char* input, size_t input_len) {
    if (input == NULL) {
        return NULL;
    }
    
    size_t len = strnlen(input, input_len);
    if (len == input_len && input_len > 0 && input[len - 1] != '\0') {
        return NULL;
    }
    
    char* result = (char*)malloc((len + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    size_t num_count = 0;
    size_t j = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (isdigit((unsigned char)input[i])) {
            num_count++;
        } else {
            result[j++] = input[i];
        }
    }
    
    for (size_t i = 0; i < len && num_count > 0; i++) {
        if (isdigit((unsigned char)input[i])) {
            result[j++] = input[i];
            num_count--;
        }
    }
    
    result[j] = '\0';
    return result;
}

int main(void) {
    const char test_str[] = "a1b2c3d4";
    size_t test_len = sizeof(test_str);
    char* result = move_numbers_to_string(test_str, test_len);
    
    if (result != NULL) {
        printf("Original: %s\n", test_str);
        printf("Modified: %s\n", result);
        free(result);
        result = NULL;
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}