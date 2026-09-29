#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_multiple_spaces(const char *input, size_t max_len)
{
    if (input == NULL)
        return NULL;

    size_t len = strnlen(input, max_len);
    char *result = malloc(len + 1);
    if (result == NULL)
        return NULL;

    size_t i = 0, j = 0;
    int space_pending = 0;

    while (i < len && isspace((unsigned char)input[i]))
        i++;

    for (; i < len; i++) {
        if (isspace((unsigned char)input[i])) {
            space_pending = 1;
        } else {
            if (space_pending && j > 0)
                result[j++] = ' ';
            result[j++] = input[i];
            space_pending = 0;
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

    printf("Enter a string: ");
    
    read_len = getline(&input, &input_size, stdin);
    if (read_len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (read_len > 0 && input[read_len - 1] == '\n') {
        input[read_len - 1] = '\0';
        read_len--;
    }

    char *cleaned = remove_multiple_spaces(input, (size_t)read_len + 1);
    if (cleaned == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Result: \"%s\"\n", cleaned);
    
    free(cleaned);
    free(input);

    return EXIT_SUCCESS;
}