#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* minimizeString(const char* str, size_t max_len, char ch) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    
    if (len == max_len && str[len - 1] != '\0') {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ch) {
            count++;
        }
    }

    if (count == len) {
        char* result = (char*)malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    char* result = (char*)malloc(len - count + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] != ch) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    char* input = NULL;
    size_t input_size = 0;
    ssize_t len;
    char ch;

    printf("Enter a string: ");
    len = getline(&input, &input_size, stdin);
    if (len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return 1;
    }

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    printf("Enter the character to remove: ");
    if (scanf(" %c", &ch) != 1) {
        fprintf(stderr, "Error reading character\n");
        free(input);
        return 1;
    }

    char* result = minimizeString(input, len + 1, ch);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(input);
        return 1;
    }

    printf("Minimized string: %s\n", result);

    free(result);
    result = NULL;
    free(input);
    input = NULL;

    return 0;
}