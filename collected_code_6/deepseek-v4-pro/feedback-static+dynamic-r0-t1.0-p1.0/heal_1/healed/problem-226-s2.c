#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* remove_odd_index_chars(const char* str, size_t max_len) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strnlen(str, max_len);
    if (len == max_len && str[max_len] != '\0') {
        return NULL;
    }
    
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (i % 2 == 0) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    
    return result;
}

int main(void) {
    const char* test_string = "abcdefghij";
    const size_t max_len = 256;
    char* modified = remove_odd_index_chars(test_string, max_len);
    
    if (modified != NULL) {
        printf("Original: %s\n", test_string);
        printf("Modified: %s\n", modified);
        free(modified);
    } else {
        printf("Failed to process string\n");
    }
    
    return 0;
}