#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *string_to_lower(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strnlen(str, 4096);
    char *result = (char *)malloc(len + 1);
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
    size_t bufsize = 0;
    printf("Enter a string: ");
    ssize_t length = getline(&input, &bufsize, stdin);
    if (length == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return 1;
    }
    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    }
    char *lower = string_to_lower(input);
    if (lower == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(input);
        return 1;
    }
    printf("Lowercase: %s\n", lower);
    free(lower);
    free(input);
    return 0;
}