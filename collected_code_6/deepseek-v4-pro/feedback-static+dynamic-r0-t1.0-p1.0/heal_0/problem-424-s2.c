#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char extract_rear_char(const char *str) {
    if (str == NULL || *str == '\0') {
        return '\0';
    }
    size_t len = strlen(str);
    return str[len - 1];
}

char *extract_rear_elements(char *arr[], size_t size) {
    if (arr == NULL || size == 0) {
        return NULL;
    }
    
    char *result = (char *)malloc(size + 1);
    if (result == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < size; i++) {
        result[i] = extract_rear_char(arr[i]);
    }
    result[size] = '\0';
    
    return result;
}

int main(void) {
    char *strings[] = {"hello", "world", "test", "example"};
    size_t size = sizeof(strings) / sizeof(strings[0]);
    
    char *rear_chars = extract_rear_elements(strings, size);
    if (rear_chars == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < size; i++) {
        printf("%c", rear_chars[i]);
    }
    printf("\n");
    
    free(rear_chars);
    return EXIT_SUCCESS;
}