#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *replace_spaces(const char *str, size_t len) {
    if (str == NULL) {
        return NULL;
    }

    size_t space_count = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ') {
            space_count++;
        }
    }

    if (space_count > (SIZE_MAX - len - 1) / 2) {
        return NULL;
    }

    size_t new_len = len + space_count * 2 + 1;
    char *result = malloc(new_len);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ') {
            result[j++] = '%';
            result[j++] = '2';
            result[j++] = '0';
        } else {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    char *input = NULL;
    size_t input_size = 0;
    ssize_t len;

    printf("Enter a string: ");
    
    len = getline(&input, &input_size, stdin);
    if (len == -1) {
        fprintf(stderr, "Error reading input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    char *modified = replace_spaces(input, (size_t)len);
    free(input);
    
    if (modified == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Modified string: %s\n", modified);

    free(modified);
    return EXIT_SUCCESS;
}