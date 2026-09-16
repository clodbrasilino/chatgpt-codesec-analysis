#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_string_into_chars(const char *str, size_t *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str);
    if (len == 0) {
        *count = 0;
        return NULL;
    }
    
    char **result = malloc(len * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < len; i++) {
        result[i] = malloc(2 * sizeof(char));
        if (result[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        result[i][0] = str[i];
        result[i][1] = '\0';
    }
    
    *count = len;
    return result;
}

void free_split_result(char **result, size_t count) {
    if (result == NULL) {
        return;
    }
    
    for (size_t i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char *input = "Hello";
    size_t count = 0;
    
    char **chars = split_string_into_chars(input, &count);
    if (chars == NULL && count > 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < count; i++) {
        printf("Character %zu: %s\n", i, chars[i]);
    }
    
    free_split_result(chars, count);
    
    return EXIT_SUCCESS;
}