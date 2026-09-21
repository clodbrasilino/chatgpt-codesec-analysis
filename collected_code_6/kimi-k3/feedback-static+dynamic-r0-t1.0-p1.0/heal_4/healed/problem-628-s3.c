#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

char *replace_spaces(const char *str, size_t max_len)
{
    size_t space_count = 0;
    size_t len = 0;
    size_t i;
    size_t j;
    char *result;

    if (str == NULL || max_len == 0) {
        return NULL;
    }

    while (len < max_len && str[len] != '\0') {
        len++;
    }

    if (len == max_len && str[len] != '\0') {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (str[i] == ' ') {
            space_count++;
        }
    }

    if (space_count > (SIZE_MAX - len - 1) / 2) {
        return NULL;
    }

    result = malloc(len + space_count * 2 + 1);
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 0; i < len; i++) {
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

int main(void)
{
    char *input = NULL;
    size_t input_size = 0;
    ssize_t input_len;
    char *output;

    printf("Enter a string: ");
    
    input_len = getline(&input, &input_size, stdin);
    if (input_len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        input_len--;
    }

    output = replace_spaces(input, (size_t)input_len + 1);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed or invalid input\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Result: %s\n", output);

    free(output);
    free(input);

    return EXIT_SUCCESS;
}