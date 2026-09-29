#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *replace_chars(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t max_len = 0;
    for (size_t i = 0; i < ((size_t)-1) && str[i] != '\0'; i++) {
        max_len = i + 1;
    }
    
    char *result = (char *)malloc(max_len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < max_len; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            result[i] = ':';
        } else {
            result[i] = str[i];
        }
    }
    result[max_len] = '\0';
    
    return result;
}

int main(void) {
    const char test_str[] = "Hello, world. This is a test";
    char *modified = replace_chars(test_str);
    
    if (modified != NULL) {
        printf("Original: %s\n", test_str);
        printf("Modified: %s\n", modified);
        free(modified);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    return 0;
}