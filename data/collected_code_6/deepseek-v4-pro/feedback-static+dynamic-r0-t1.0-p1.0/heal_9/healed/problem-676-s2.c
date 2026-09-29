#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static char* safe_malloc(size_t size) {
    if (size == 0 || size >= SIZE_MAX) {
        return NULL;
    }
    return (char*)malloc(size);
}

char* remove_non_alphanumeric(const char* input) {
    size_t len;
    size_t src_pos = 0;
    size_t dst_pos = 0;
    char* result;
    size_t result_size;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, SIZE_MAX - 1);
    
    if (len >= SIZE_MAX - 1) {
        return NULL;
    }
    
    result_size = len + 1;
    result = safe_malloc(result_size);
    if (result == NULL) {
        return NULL;
    }

    if (len == 0) {
        result[0] = '\0';
        return result;
    }

    for (src_pos = 0; src_pos < len; src_pos++) {
        char current_char = input[src_pos];
        
        if ((current_char >= 'a' && current_char <= 'z') ||
            (current_char >= 'A' && current_char <= 'Z') ||
            (current_char >= '0' && current_char <= '9')) {
            
            if (dst_pos >= len) {
                break;
            }
            result[dst_pos] = current_char;
            dst_pos++;
        }
    }

    result[dst_pos] = '\0';
    
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