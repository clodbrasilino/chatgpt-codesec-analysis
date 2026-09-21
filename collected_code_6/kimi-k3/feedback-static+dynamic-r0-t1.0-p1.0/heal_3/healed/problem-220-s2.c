#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_chars(const char *str, size_t n, size_t max_len) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, max_len);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t count = 0;
    size_t i = 0;

    while (i < len) {
        if ((str[i] == ' ' || str[i] == ',' || str[i] == '.') && count < n) {
            result[i] = ':';
            count++;
        } else {
            result[i] = str[i];
        }
        i++;
    }
    result[len] = '\0';

    return result;
}

int main(void) {
    char *input = NULL;
    size_t input_size = 0;
    size_t n;

    printf("Enter a string: ");
    ssize_t read = getline(&input, &input_size, stdin);
    if (read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (read > 0 && (size_t)read <= input_size && input[read - 1] == '\n') {
        input[read - 1] = '\0';
        read--;
    }

    printf("Enter maximum number of replacements: ");
    if (scanf("%zu", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        free(input);
        return EXIT_FAILURE;
    }

    char *result = replace_chars(input, n, (size_t)read + 1);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Result: %s\n", result);

    free(result);
    free(input);
    return EXIT_SUCCESS;
}