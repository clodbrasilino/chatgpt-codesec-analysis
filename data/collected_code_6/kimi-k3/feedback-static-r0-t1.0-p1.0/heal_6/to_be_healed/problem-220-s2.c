#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_chars(const char *str, size_t n) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    size_t max_len = 4096;
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
    ssize_t len = getline(&input, &input_size, stdin);
    if (len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'len' is assigned a value that is never used. [unreadVariable]
         */
        len--;
    }

    printf("Enter maximum number of replacements: ");
    if (scanf("%zu", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        free(input);
        return EXIT_FAILURE;
    }

    char *result = replace_chars(input, n);
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