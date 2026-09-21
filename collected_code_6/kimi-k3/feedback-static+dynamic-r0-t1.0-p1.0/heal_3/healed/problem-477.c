#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *to_lowercase(const char *str, size_t max_len) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    
    if (len == max_len && str[len] != '\0') {
        return NULL;
    }
    
    char *result = malloc(len + 1);
    
    if (result == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < len; i++) {
        result[i] = tolower((unsigned char)str[i]);
    }
    result[len] = '\0';
    
    return result;
}

int main(void) {
    char *input = NULL;
    size_t input_size = 0;
    ssize_t chars_read;
    
    chars_read = getline(&input, &input_size, stdin);
    
    if (chars_read == -1) {
        free(input);
        return 1;
    }
    
    size_t len = strcspn(input, "\n");
    input[len] = '\0';
    
    char *lower = to_lowercase(input, chars_read + 1);
    
    if (lower == NULL) {
        free(input);
        return 1;
    }
    
    printf("%s\n", lower);
    free(lower);
    free(input);
    
    return 0;
}