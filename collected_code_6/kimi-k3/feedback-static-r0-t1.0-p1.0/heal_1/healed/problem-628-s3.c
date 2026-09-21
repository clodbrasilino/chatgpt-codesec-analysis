#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_spaces(const char *str, size_t max_len)
{
    size_t space_count = 0;
    size_t len;
    size_t i;
    size_t j;
    char *result;

    if (str == NULL) {
        return NULL;
    }

    len = strnlen(str, max_len);

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
    ssize_t read_len;
    char *output;

    printf("Enter a string: ");
    read_len = getline(&input, &input_size, stdin);
    if (read_len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (read_len > 0 && input[read_len - 1] == '\n') {
        input[read_len - 1] = '\0';
    }

    output = replace_spaces(input, read_len);
    free(input);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Result: %s\n", output);

    free(output);
    output = NULL;

    return EXIT_SUCCESS;
}